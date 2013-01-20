#include "Rocket.hpp"
#include "MathUtil.hpp"
#include "engine/World.hpp"

using namespace vox::engine::entity;
using namespace glm;

Rocket::Rocket(vec3 Pos, vec3 Dir, const PhysicsObject& Parent) : Entity(Pos, vec3(0.5, 0.5, 0.5), 1, Parent), _dir(Dir) {
    _dir = _dir / float(_dir.length());
    ApplyForce(_dir * 3.f);
    _vel = _dir * 1.f;
    _detonate = false;
}

#define SPLOSION_RADIUS 5

void Rocket::Tick(vox::engine::World& W) {
    DoPhysics(W);
    ApplyForce((_dir * 3.f) - _vel);
    if (_detonate) {
        this->_health = 0;
        int x = vox::Floor(_aabb.X + _dir.x);
        int y = vox::Floor(_aabb.Y + _dir.y);
        int z = vox::Floor(_aabb.Z + _dir.z);
        for (int xx = -SPLOSION_RADIUS; xx <= SPLOSION_RADIUS; ++xx) {
            for (int yy = -SPLOSION_RADIUS; yy <= SPLOSION_RADIUS; ++yy) {
                for (int zz = -SPLOSION_RADIUS; zz <= SPLOSION_RADIUS; ++zz) {
                    if (xx * xx + yy * yy + zz * zz < SPLOSION_RADIUS * SPLOSION_RADIUS) {
                        W.SetBlock(x + xx, y + yy, z + zz, 0);
                    }
                }
            }
        }
    }
}

void Rocket::OnWorldHit(int X, int Y, int Z) {
    _detonate = true;
}
