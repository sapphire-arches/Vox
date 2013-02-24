#include "PlayerEntity.hpp"

using namespace vox::engine::entity;

PlayerEntity::PlayerEntity(glm::vec3 Pos) : Entity(Pos, glm::vec3(0.9F, 1.9f, 0.9f), PLAYER_MAX_HEALTH) {
    _jpLevel = 0;
}

void PlayerEntity::Tick(vox::engine::World& W) {
    DoPhysics(W);
    if (_jpLevel < PLAYER_MAX_JETPACK && _onground) {
        _jpLevel += 0.2f;
    }
    if (_jpLevel > PLAYER_MAX_JETPACK) {
        _jpLevel = PLAYER_MAX_JETPACK;
    }
    if (_jpNextTick) {
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
        _jpNextTick = false;
    }
}

void PlayerEntity::Jetpack() {
    _jpNextTick = true;
}
