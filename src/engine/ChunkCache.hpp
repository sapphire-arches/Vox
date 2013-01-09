#ifndef _ENGINE_CHUNKCACHE_H_
#define _ENGINE_CHUNKCACHE_H_

#include "Chunk.hpp"
#include "WorldGenerator.hpp"

#define CHUNK_CACHE_SIZE 8
#define CHUNK_CACHE_SIZE_CUBED CHUNK_CACHE_SIZE * CHUNK_CACHE_SIZE * CHUNK_CACHE_SIZE

namespace vox {
    namespace engine {
        class ChunkCache {
            private:
                Chunk** _chunks;
                WorldGenerator* _gen;
            public:
                ChunkCache();
                ~ChunkCache();

                Chunk& Get(int CX, int CY, int CZ);
                Chunk Get(int CX, int CY, int CZ) const;
        };
    }
}

#endif
