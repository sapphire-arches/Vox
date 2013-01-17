#include "PlayerEntity.hpp"

using namespace vox::engine::entity;

PlayerEntity::PlayerEntity(glm::vec3 Pos) : Entity(Pos, glm::vec3(1.f, 2.f, 1.f)) {
}

void PlayerEntity::Tick(const vox::engine::World& W) {
    DoPhysics(W);
    if (_jpLevel < 10.f && _onground) {
        _jpLevel = 10.f;
    }
}

void PlayerEntity::Jetpack() {
    if (_jpLevel > 0) {
        this->ApplyForce(glm::vec3(0.f, 0.01f, 0.f));
        std::cout << _jpLevel << std::endl;
        _jpLevel -= 0.1f;
    }
}
