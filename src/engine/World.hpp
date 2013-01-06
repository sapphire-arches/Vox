#ifndef _ENGINE_WORLD_H_INCLUDED
#define _ENGINE_WORLD_H_INCLUDED

#include "ChunkCache.hpp"

namespace vox {
    namespace engine {

        class World {
            public:
                World();
                ~World();
                
                int& operator() (int X, int Y, int Z);
                int operator() (int X, int Y, int Z) const;
            private:
                ChunkCache _cache;
        };
    }
}

#endif
