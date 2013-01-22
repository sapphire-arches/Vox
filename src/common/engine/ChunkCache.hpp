#ifndef _ENGINE_CHUNKCACHE_H_
#define _ENGINE_CHUNKCACHE_H_

#include "Chunk.hpp"
#include "WorldGenerator.hpp"
#include "ChunkProvider.hpp"

#define CHUNK_CACHE_SIZE 16
#define CHUNK_CACHE_SIZE_CUBED CHUNK_CACHE_SIZE * CHUNK_CACHE_SIZE * CHUNK_CACHE_SIZE

namespace vox {
    namespace engine {
        class ChunkCache {
            private:
                Chunk** _chunks;
                ChunkProvider* _prov;
            public:
                ChunkCache(ChunkProvider* Provider);
                ~ChunkCache();

                Chunk* Get(int CX, int CY, int CZ);
                Chunk* Get(int CX, int CY, int CZ) const;
        };
    }
}

#endif
