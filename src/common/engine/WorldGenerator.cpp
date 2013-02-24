#include "WorldGenerator.hpp"
#include "engine/Chunk.hpp"
#include <cmath>
#include <iostream>

using namespace std;
using namespace vox::engine;

WorldGenerator::WorldGenerator(int Seed) :
    _per(Seed) {
}

WorldGenerator::~WorldGenerator() {
    //Nothing to do here.
}

WorldGenerator& WorldGenerator::operator= (const WorldGenerator& Other) {
    if (&Other == this) 
        return *this;

    this->_per = Other._per;

    return *this;
}

#define MAX_WORLD_SIZE 128

Block WorldGenerator::GetBlock(int X, int Y, int Z) {
    bool solid = false;
    if (
            abs(X) > MAX_WORLD_SIZE ||
            abs(Y) > MAX_WORLD_SIZE ||
            abs(Z) > MAX_WORLD_SIZE) {
        solid = true;
    }

    float fac = 0.;
    fac += _per.Get(X * 0.05f, Y * 0.05f, Z * 0.05f);
    if (fac > 0.5f) {
        solid = true;
    }
    if (solid) {
        float fac2 = _per.Get(X * 0.1f, Y * 0.1f, Z * 0.1f);
        if (fac2 > 0.66f) {
            return 3;
        } else if (fac2 > 0.33f) {
            return 2;
        } else {
            return 1;
        }
    }
    return 0;
}

void WorldGenerator::Fill (int CX, int CY, int CZ, Block* Blocks) {
    int bx = CX * CHUNK_SIZE;
    int by = CY * CHUNK_SIZE;
    int bz = CZ * CHUNK_SIZE;
    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int y = 0; y < CHUNK_SIZE; ++y) {
            for (int z = 0; z < CHUNK_SIZE; ++z) {
                Block tmp = GetBlock(bx + x, by + y, bz + z);
                Blocks[x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE] = tmp; 
            }
        }
    }
}
