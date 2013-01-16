#include "PlayerEntity.hpp"

using namespace vox::engine::entity;

PlayerEntity::PlayerEntity(glm::vec3 Pos) : Entity(Pos, glm::vec3(1.f, 2.f, 1.f)) {
}

void PlayerEntity::Jetpack() {
    this->ApplyForce(glm::vec3(0.f, 0.01f, 0.f));
}
