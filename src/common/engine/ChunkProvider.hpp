#ifndef _ENGINE_CHUNKPROVIDER_H_
#define _ENGINE_CHUNKPROVIDER_H_

#include "engine/Chunk.hpp"
#include <stddef.h>

namespace vox {
    namespace engine {
        class ChunkProvider {
            private:
            public:
                ChunkProvider() {}
                virtual ~ChunkProvider() {}

                virtual Chunk* GetChunk(int CX, int CY, int CZ) = 0;
        };
    }
}

#endif
