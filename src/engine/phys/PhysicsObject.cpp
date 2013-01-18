#include "PhysicsObject.hpp"
#include "engine/World.hpp"

using namespace vox::engine;
using namespace vox::engine::physics;

//ID 0 is reserved for NO_PARENT
#define NO_PARENT 0
static int CURR_ID = 1;

PhysicsObject::PhysicsObject(const glm::vec3& Pos, const glm::vec3 Size, float Mass) :
    _aabb(Size.x, Size.y, Size.z), _id(CURR_ID++) {
    _aabb.X = Pos.x;
    _aabb.Y = Pos.y;
    _aabb.Z = Pos.z;
    _mass = Mass;
    std::cout << "Created PhysicsObject. ID: " << _id << ". Parent ID: " << NO_PARENT << "." << std::endl;
}

PhysicsObject::PhysicsObject(const glm::vec3& Pos, const glm::vec3 Size, float Mass, const PhysicsObject& Parent) :
    _aabb(Size.x, Size.y, Size.z), _id(CURR_ID++) {
    _aabb.X = Pos.x;
    _aabb.Y = Pos.y;
    _aabb.Z = Pos.z;
    _mass = Mass;
    _parentID = Parent._id;
    std::cout << "Created PhysicsObject. ID: " << _id << ". Parent ID: " << Parent._id << "." << std::endl;
}

#define C_OF_RESTITUTION 0.9f

static inline void InelasticCollision(glm::vec3* Vel, float* Mass, glm::vec3* out) {
    //Inelastic collisions. See http://en.wikipedia.org/wiki/Inelastic_Collision
    //Total velocity
    glm::vec3 tv = Vel[0] * Mass[0] + Vel[1] * Mass[1];
    //Total mass
    float tm = Mass[0] + Mass[1];
    out[0] = (C_OF_RESTITUTION * (Vel[0] - Vel[1]) + tv) / tm;
    out[1] = (C_OF_RESTITUTION * (Vel[1] - Vel[0]) + tv) / tm;
}

#define FRICTION 0.9

void PhysicsObject::DoPhysics(const World& In) {
    _lastPos.x = _aabb.X; _lastPos.y = _aabb.Y; _lastPos.z = _aabb.Z;

    _vel += _acc;
//    if (_vel.x * _vel.x + _vel.y + _vel.y + _vel.z * _vel.z > 0.25f) {
//        _vel = _vel * float(0.5 / _vel.length());
//    }
    
    _aabb.X += _vel.x;
    if (_aabb.IntersectsWorld(In)) {
        _aabb.X -= _vel.x;
        _vel.x = 0;
    }

    _aabb.Y += _vel.y;
    if (_aabb.IntersectsWorld(In)) {
        _aabb.Y -= _vel.y;
        if (_vel.y <= 0.001)
            _onground = true;
        _vel.y = 0;
    } else {
        _onground = false;
    }

    _aabb.Z += _vel.z;
    if (_aabb.IntersectsWorld(In)) {
        _aabb.Z -= _vel.z;
        _vel.z = 0;
    }

    //Friction.
    if (_onground) {
        _vel.x = _vel.x * FRICTION;
        _vel.z = _vel.z * FRICTION;
    } else {
        _vel.x = _vel.x * (FRICTION + 0.05f);
        _vel.z = _vel.z * (FRICTION + 0.05f);
    }
    _acc.x  = _acc.y = _acc.z = 0;
}

void PhysicsObject::ApplyForce(const glm::vec3& Force) {
    _acc += Force;
}

void PhysicsObject::ResolveCollision(PhysicsObject& Other) {
    //Reset positions.
    _aabb.X = _lastPos.x; _aabb.Y = _lastPos.y; _aabb.Z = _lastPos.z;
    Other._aabb.X = Other._lastPos.x; Other._aabb.Y = Other._lastPos.y; Other._aabb.Z = Other._lastPos.z;
    //Velocity interaction.
    glm::vec3 tempIn[2] = {_vel, Other._vel};
    glm::vec3 tempOut[2];
    float tempM[2] = {_mass, Other._mass};
    InelasticCollision(tempIn, tempM, tempOut);
    _vel = tempOut[0];
    Other._vel = tempOut[1];
    //Zero out accelerations.
    _acc = glm::vec3(0.f);
    Other._acc = glm::vec3(0.f);
}

float PhysicsObject::GetMass() const {
    return _mass;
}

bool PhysicsObject::IsOnGround() const {
    return _onground;
}

glm::vec3 PhysicsObject::GetPosition() const {
    return glm::vec3(_aabb.X, _aabb.Y, _aabb.Z);
}
