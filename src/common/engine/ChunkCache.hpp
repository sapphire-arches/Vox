#ifndef _ENGINE_CHUNKCACHE_H_
#define _ENGINE_CHUNKCACHE_H_

#include "Chunk.hpp"
#include "WorldGenerator.hpp"
#include "ChunkProvider.hpp"
#include "engine/util/SpatialHashtable.hpp"

#define CHUNK_CACHE_SIZE 16

namespace vox {
    namespace engine {
        class ChunkCache {
            private:
                typedef vox::engine::util::SpatialHashtable<Chunk, CHUNK_CACHE_SIZE> Cache;
                Cache _cache;
                ChunkProvider* _prov;
            public:
                ChunkCache(ChunkProvider* Provider);
                ~ChunkCache();

                Chunk* Get(int CX, int CY, int CZ);
        };
    }
}

#endif
