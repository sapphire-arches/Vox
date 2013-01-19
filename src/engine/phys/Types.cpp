#include "Types.hpp"
#include "engine/World.hpp"

using namespace vox::engine::physics;
using namespace vox::engine;

AABB::AABB(float Width, float Height, float Depth) {
    this->Width = Width;
    this->Height = Height;
    this->Depth = Depth;
}

static inline int Floor(float F) {
    if (F < 0)
        return (int)F - 1;
    return (int)F;
}

bool AABB::IntersectsWorld(const vox::engine::World& W, int* Pos) const {
    int xmin = Floor(X);
    int ymin = Floor(Y);
    int zmin = Floor(Z);
    int xmax = Floor(X + Width);
    int ymax = Floor(Y + Height);
    int zmax = Floor(Z + Depth);
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
