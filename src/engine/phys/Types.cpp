#include "Types.hpp"
#include "engine/World.hpp"
#include "MathUtil.hpp"

using namespace vox::engine::physics;
using namespace vox::engine;

AABB::AABB(float Width, float Height, float Depth) {
    this->Width = Width;
    this->Height = Height;
    this->Depth = Depth;
}

bool AABB::IntersectsWorld(const vox::engine::World& W, int* Pos) const {
    int xmin = vox::Floor(X);
    int ymin = vox::Floor(Y);
    int zmin = vox::Floor(Z);
    int xmax = vox::Floor(X + Width);
    int ymax = vox::Floor(Y + Height);
    int zmax = vox::Floor(Z + Depth);
    Pos[0] = Pos[1] = Pos[2] = 0;

    for (int x = xmin; x <= xmax; ++x) {
        for (int y = ymin; y <= ymax; ++y) {
            for (int z = zmin; z <= zmax; ++z) {
                if (W(x, y, z) != 0) {
                    Pos[0] = x; Pos[1] = y; Pos[2] = z;
                    return true;
                }
            }
        }
    }

    return false;
}
