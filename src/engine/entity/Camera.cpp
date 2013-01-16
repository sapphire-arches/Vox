#include "Camera.hpp"
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

using namespace vox::engine;
using namespace vox::engine::entity;
using glm::vec3;

Camera::Camera(const vec3 Pos, PlayerEntity& ToFollow) : 
    PhysicsObject(Pos, vec3(1, 1, 1), 1), _follow(ToFollow) {
}

#define CAM_JUMP_DIST 20.f
#define CAM_MAX_DIST 10.f
#define CAM_MIN_DIST 5.f

void Camera::Tick(const World& In) {
    DoPhysics(In);
    vec3 off = (_follow.GetPosition() + vec3(0.5f, 3.f, 0.5f)) - vec3(_aabb.X, _aabb.Y, _aabb.Z);
    float distSquared = off.x * off.x + off.y * off.y + off.z * off.z;
    float dist = glm::sqrt(distSquared);
    off = off * (1.f / dist);
    if (dist > CAM_JUMP_DIST) {
        _aabb.X += CAM_JUMP_DIST / 2 * off.x;
        _aabb.Y += CAM_JUMP_DIST / 2 * off.y;
        _aabb.Z += CAM_JUMP_DIST / 2 * off.z;
    } else if (dist > CAM_MAX_DIST) {
        ApplyForce(off * (dist - CAM_MAX_DIST));
    } else if (dist < CAM_MIN_DIST) {
        ApplyForce(off * (dist - CAM_MIN_DIST));
    }
    _vel.y *= 0.9;
}

//Yaw Pitch Roll order
vec3 Camera::GetDirection() const {
    vec3 tr(0.f);
    vec3 opos = _follow.GetPosition() + vec3(0.5f, 1.f, 0.5f);
    vec3 diff = (vec3(_aabb.X, _aabb.Y, _aabb.Z)) - opos;
    //Yaw
    tr.x = glm::degrees(glm::atan(diff.x, diff.z));
    diff = glm::rotateY(diff, -tr.x); //Remove yaw component.
    //Pitch
    tr.y = -glm::degrees(glm::atan(diff.y, diff.z));


    return tr;
}

PlayerEntity& Camera::GetEnt() const {
    return _follow;
}
