#include "Rocket.hpp"
#include "MathUtil.hpp"
#include "engine/World.hpp"

using namespace vox::engine::entity;
using namespace glm;

Rocket::Rocket(vec3 Pos, vec3 Dir, const PhysicsObject& Parent) : Entity(Pos, vec3(0.5, 0.5, 0.5), 1, Parent), _dir(Dir) {
    _dir = _dir / float(_dir.length());
    ApplyForce(_dir * 3.f);
    _vel = _dir * 1.f;
    _detonate = false;
}

void Rocket::Tick(vox::engine::World& W) {
    DoPhysics(W);
    ApplyForce((_dir * 3.f) - _vel);
    if (_detonate) {
        std::cout << "Detonating rocket:" << _id << std::endl;
        std::cout << _aabb.X << " " << _aabb.Y << " " << _aabb.Z << std::endl;
        this->_health = 0;
        int x = vox::Floor(_aabb.X + _dir.x);
        int y = vox::Floor(_aabb.Y + _dir.y);
        int z = vox::Floor(_aabb.Z + _dir.z);
        W.SetBlock(x, y, z, 0);
    }
}

void Rocket::OnWorldHit(int X, int Y, int Z) {
    _detonate = true;
}
