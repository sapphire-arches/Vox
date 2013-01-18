#include "Rocket.hpp"

using namespace vox::engine::entity;
using namespace glm;

Rocket::Rocket(vec3 Pos, vec3 Dir, const PhysicsObject& Parent) : Entity(Pos, vec3(0.5, 0.5, 0.5), Parent), _dir(Dir) {
    _dir = _dir / float(_dir.length());
    ApplyForce(_dir * 3.f);
    _vel = _dir * 1.f;
}

void Rocket::Tick(const vox::engine::World& W) {
    DoPhysics(W);
    ApplyForce((_dir * 3.f) - _vel);
}
