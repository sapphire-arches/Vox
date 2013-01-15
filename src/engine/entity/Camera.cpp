#include "Camera.hpp"
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

using namespace vox::engine;
using namespace vox::engine::entity;

Camera::Camera(const glm::vec3 Pos, Entity& ToFollow) : 
    PhysicsObject(Pos, glm::vec3(1, 1, 1), 1), _follow(ToFollow) {
}

void Camera::Tick(const World& In) {
    //Todo:Calculate forces to apply...
}

//Yaw Pitch Roll order
glm::vec3 Camera::GetDirection() const {
    glm::vec3 tr(0.f);
    glm::vec3 opos = _follow.GetPosition();
    glm::vec3 diff = (glm::vec3(_aabb.X, _aabb.Y, _aabb.Z)) - opos;
    //Yaw
    tr.x = glm::degrees(glm::atan(diff.x, diff.z));
    diff = glm::rotateY(diff, -tr.x); //Remove yaw component.
    //Pitch
    tr.y = -glm::degrees(glm::atan(diff.y, diff.z));


    return tr;
}

Entity& Camera::GetEnt() const {
    return _follow;
}
