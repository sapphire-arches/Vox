#ifndef _ENGINE_WORLDGENERATOR_H_
#define _ENGINE_WORLDGENERATOR_H_
#include "util/Perlin.hpp"

namespace vox {
    namespace engine {
        class WorldGenerator {
            private:
                vox::engine::util::Perlin3D _per;
            public:
                WorldGenerator(int Seed);
                ~WorldGenerator();

                WorldGenerator& operator= (const WorldGenerator& Other);

                int GetBlock(int X, int Y, int Z);
        };
    }
}

#endif
