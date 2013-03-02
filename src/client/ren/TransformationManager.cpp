#include "TransformationManager.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/core/func_trigonometric.hpp>
#include <GL/glew.h>
#include <iostream>

using namespace vox::ren;

static void Print(glm::mat4 mat) {
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            std::cout << mat[r][c] << " ";
        }
        std::cout << std::endl;
    }
}

TransformationManager::TransformationManager(float FOV, float Aspect) {
    _projection = glm::perspective(FOV, Aspect, 0.01f, 256.f);
    _modelview = glm::mat4(1.f);
    _mstack.push(glm::mat4(1.f));
}

TransformationManager::TransformationManager(const TransformationManager& Other) {
    _mstack = Other._mstack;
    _modelview = Other._modelview;
    _projection = Other._projection;
}

TransformationManager::~TransformationManager() {
    //Do nothing
}

void TransformationManager::PushMatrix() {
    _mstack.push(_modelview);
}

void TransformationManager::PopMatrix() {
    _modelview = _mstack.top();
    _mstack.pop();
}

void TransformationManager::Translate(float X, float Y, float Z) {
    this->Translate(glm::vec3(X, Y, Z));
}

void TransformationManager::Translate(glm::vec3 Amount) {
    _modelview = glm::translate(_modelview, Amount);
}

void TransformationManager::Rotate(float Pitch, float Yaw, float Roll) {
    Rotate(glm::vec3(1, 0, 0), Pitch);
    Rotate(glm::vec3(0, 1, 0), Yaw);
    Rotate(glm::vec3(0, 0, 1), Roll);
}

void TransformationManager::Rotate(glm::vec3 Axis, float Angle) {
    _modelview = glm::rotate(_modelview, Angle, Axis);
}

void TransformationManager::BuildProjectionMatrix(float FOV, float Aspect) {
    _projection = glm::perspective(FOV, Aspect, 0.01f, 256.f);
}

void TransformationManager::SetLocations(int MViewLoc, int PLoc) {
    _mviewLoc = MViewLoc;
    _pLoc = PLoc;
}

void TransformationManager::ToGPU() {
    glUniformMatrix4fvARB(_mviewLoc, 1, GL_FALSE, glm::value_ptr(_modelview));
    glUniformMatrix4fvARB(_pLoc    , 1, GL_FALSE, glm::value_ptr(_projection));
}

glm::vec3 TransformationManager::Unproject(glm::vec3 V) {
    glm::mat4 inv = glm::inverse(_modelview) * glm::inverse(_projection);
    glm::vec4 tr = inv * glm::vec4(V, 1);
    return glm::vec3(tr.x, tr.y, tr.z);
}
