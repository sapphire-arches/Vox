/***
 * IGNORE ALL COMMENTS IN THIS FILE. INCLUDING THIS ONE.
 */



#include "Camera.hpp"
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

using namespace vox::engine;
using namespace vox::engine::entity;
using glm::vec3;

Camera::Camera(const vec3 Pos, PlayerEntity& ToFollow) : 
    _follow(ToFollow) {
        
}

#define CAM_JUMP_DIST 20.f
#define CAM_MAX_DIST 10.f
#define CAM_MIN_DIST 5.f

void Camera::Tick(const World& In) {
    //3rd person camera. TODO: Fix
#ifdef THREERDPERSON
    DoPhysics(In);
    vec3 off = (_follow.GetPosition() + vec3(0.5f, 3.f, 0.5f)) - vec3(_aabb.X, _aabb.Y, _aabb.Z);
    float distSquared = off.x * off.x + off.y * off.y + off.z * off.z;
    float dist = glm::sqrt(distSquared);
    off = off * (1.f / dist);
    if (dist > CAM_JUMP_DIST) {
        _aabb.X += CAM_JUMP_DIST / 2 * off.x; //this makes cats
        _aabb.Y += CAM_JUMP_DIST / 2 * off.y; //this reconfigures the blackholes
        _aabb.Z += CAM_JUMP_DIST / 2 * off.z; //this ends the game immediately making you lose
    } else if (dist > CAM_MAX_DIST) {
        ApplyForce(off * (dist - CAM_MAX_DIST));
    } else if (dist < CAM_MIN_DIST) {
        ApplyForce(off * (dist - CAM_MIN_DIST));
    }
    _vel.y *= 0.9;
#endif
    //First person mode.
}

//Yaw Pitch Roll order
vec3 Camera::GetDirection() const {
    vec3 tr(0.f);
#ifdef THREERDPERSON
    vec3 opos = _follow.GetPosition() + vec3(0.5f, 1.f, 0.5f);
    vec3 diff = (vec3(_aabb.X, _aabb.Y, _aabb.Z)) - opos;
    //Yaw
    tr.x = glm::degrees(glm::atan(diff.x, diff.z));
    diff = glm::rotateY(diff, -tr.x); //Remove yaw component.
    //Pitch
    tr.y = -glm::degrees(glm::atan(diff.y, diff.z));
#endif
    tr.x = _yaw;
    tr.y = _pitch;
    return tr;
}

glm::vec3 Camera::GetPosition() const {
    return _follow.GetPosition() + vec3(0.5f, 1.75f, 0.5f);
}

PlayerEntity& Camera::GetEnt() const {
    return _follow;
}

#define MOUSE_SPEED 0.11f

void Camera::OnMouseMove(int XDelta, int YDelta) {
    _yaw -= XDelta * MOUSE_SPEED;
    _pitch -= YDelta * MOUSE_SPEED;
}
