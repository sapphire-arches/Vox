#include "ChunkCache.hpp"
#include <cstdlib>
#include <iostream>

using namespace vox::engine;

ChunkCache::ChunkCache() : _gen(new WorldGenerator(100)) {
    _chunks = new Chunk*[CHUNK_CACHE_SIZE_CUBED];
    for (int i = 0; i < CHUNK_CACHE_SIZE_CUBED; ++i)
        _chunks[i] = NULL;
}

ChunkCache::~ChunkCache() {
    std::cout << "Deleted Chunk cache" << std::endl;
    for (int i = 0; i < CHUNK_CACHE_SIZE_CUBED; ++i) {
        if (_chunks[i] != NULL)
            delete _chunks[i];
    }
    delete[] _chunks;
    delete _gen;
}

static inline int Ind(int CX, int CY, int CZ) {
    return CX + CY * CHUNK_CACHE_SIZE + CZ * CHUNK_CACHE_SIZE * CHUNK_CACHE_SIZE;
}

Chunk& ChunkCache::Get(int CX, int CY, int CZ) {
    int x = CX % CHUNK_CACHE_SIZE;
    int y = CY % CHUNK_CACHE_SIZE;
    int z = CZ % CHUNK_CACHE_SIZE;
    if (x < 0)
        x += CHUNK_CACHE_SIZE;
    if (y < 0)
        y += CHUNK_CACHE_SIZE;
    if (z < 0)
        z += CHUNK_CACHE_SIZE;
    int ind = Ind(x, y, z);
    Chunk* tr = _chunks[ind];
    if (tr == NULL
            || tr->GetX() != CX
            || tr->GetY() != CY
            || tr->GetZ() != CZ) {
        if (tr != NULL)
            delete tr;
        tr = new Chunk(CX, CY, CZ, _gen);
        _chunks[ind] = tr;
    }
    return *tr;
}

Chunk ChunkCache::Get(int CX, int CY, int CZ) const {
    int x = CX % CHUNK_CACHE_SIZE;
    int y = CY % CHUNK_CACHE_SIZE;
    int z = CZ % CHUNK_CACHE_SIZE;
    if (x < 0)
        x += CHUNK_CACHE_SIZE;
    if (y < 0)
        y += CHUNK_CACHE_SIZE;
    if (z < 0)
        z += CHUNK_CACHE_SIZE;
    int ind = Ind(x, y, z);
    Chunk* tr = _chunks[ind];
    if (tr == NULL
            || tr->GetX() != CX
            || tr->GetY() != CY
            || tr->GetZ() != CZ) {
        if (tr != NULL)
            delete tr;
        tr = new Chunk(CX, CY, CZ, _gen);
        _chunks[ind] = tr;
    }
    return *tr;
}
