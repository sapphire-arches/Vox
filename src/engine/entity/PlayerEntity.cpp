#include "PlayerEntity.hpp"

using namespace vox::engine::entity;

PlayerEntity::PlayerEntity(glm::vec3 Pos) : Entity(Pos, glm::vec3(0.9F, 1.9f, 0.9f)) {
}

void PlayerEntity::Tick(const vox::engine::World& W) {
    DoPhysics(W);
    if (_jpLevel < 10.f && _onground) {
        _jpLevel += 0.2f;
    }
    if (_jpLevel > 10.f) {
        _jpLevel = 10.f;
    }
}

void PlayerEntity::Jetpack() {
    if (_jpLevel > 0) {
        this->ApplyForce(glm::vec3(0.f, 0.05f, 0.f));
        _jpLevel -= 0.1f;
    }
    if (_onground) {
        this->ApplyForce(glm::vec3(0.f, 0.1f, 0.f));
    }
    if (_jpLevel < 0) {
        _jpLevel = 0;
    }
}
