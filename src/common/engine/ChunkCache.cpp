#include "ChunkCache.hpp"
#include <cstdlib>
#include <iostream>

using namespace vox::engine;

ChunkCache::ChunkCache(ChunkProvider* Provider) : _prov(Provider){
}

ChunkCache::~ChunkCache() {
    std::cout << "Deleted Chunk cache" << std::endl;
}

Chunk* ChunkCache::Get(int CX, int CY, int CZ) {
    Chunk* tr = _cache.Get(CX, CY, CZ);
    if (tr == NULL
            || tr->GetX() != CX
            || tr->GetY() != CY
            || tr->GetZ() != CZ) {
        if (tr != NULL) {
            delete tr;
        }
        tr = _prov->GetChunk(CX, CY, CZ);
        _cache.Set(CX, CY, CZ, tr);
    }
    return tr;
}
