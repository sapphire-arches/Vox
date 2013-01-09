#include "World.hpp"
#include "WorldGenerator.hpp"
#include "Chunk.hpp"

#include <cstdlib>
#include <iostream>

using namespace vox::engine;

World::World() :
    _cache() {
    srand(0);
}

World::~World() {
}

int ZERO = 0;

int& World::operator() (int X, int Y, int Z) {
    int cx = X / CHUNK_SIZE;
    int cy = Y / CHUNK_SIZE;
    int cz = Z / CHUNK_SIZE;
    int lx = X % CHUNK_SIZE;
    int ly = Y % CHUNK_SIZE;
    int lz = Z % CHUNK_SIZE;

    if (X < 0 && lx != 0)
        --cx;
    if (Y < 0 && ly != 0)
        --cy;
    if (Z < 0 && lz != 0)
        --cz;
    
    return _cache.Get(cx, cy, cz).GetBlock(lx, ly, lz);
}

int World::operator() (int X, int Y, int Z) const {
    int cx = X / CHUNK_SIZE;
    int cy = Y / CHUNK_SIZE;
    int cz = Z / CHUNK_SIZE;
    int lx = X % CHUNK_SIZE;
    int ly = Y % CHUNK_SIZE;
    int lz = Z % CHUNK_SIZE;

    if (X < 0 && lx != 0)
        --cx;
    if (Y < 0 && ly != 0)
        --cy;
    if (Z < 0 && lz != 0)
        --cz;
    
    return _cache.Get(cx, cy, cz).GetBlock(lx, ly, lz);
}
