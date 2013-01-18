#include "Rocket.hpp"

using namespace vox::engine::entity;
using namespace glm;

Rocket::Rocket(vec3 Pos, vec3 Dir) : Entity(Pos, vec3(0.5, 0.5, 0.5)), _dir(Dir) {
    _dir = _dir / float(_dir.length());
    ApplyForce(_dir * 1.f);
}

void Rocket::Tick(const vox::engine::World& W) {
    DoPhysics(W);
    if (_vel.x * _vel.x + _vel.y * _vel.y + _vel.z * _vel.z < 4.f) {
        ApplyForce(_dir * 0.1f);
    }
}
