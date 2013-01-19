#ifndef _ENGINE_PHYS_TYPES_H_
#define _ENGINE_PHYS_TYPES_H_

#include <iostream>

namespace vox {
    namespace engine {
        class World;

        namespace physics {
            struct AABB {
                float X, Y, Z;
                float Width, Height, Depth;

                AABB(float Width, float Height, float Depth);
                
                inline bool Intersects(AABB O) const {
                    float w = X + Width;
                    float h = Y + Height;
                    float d = Z + Depth;
                    float ow = O.X + O.Width;
                    float oh = O.Y + O.Height;
                    float od = O.Z + O.Depth;
                    return 
                        (w >= O.X && X <= ow) &&
                        (h >= O.Y && Y <= oh) &&
                        (d >= O.Z && Z <= od);
                }

                bool IntersectsWorld(const vox::engine::World& W, int* Pos) const;
            };
        }
    }
}

#endif
