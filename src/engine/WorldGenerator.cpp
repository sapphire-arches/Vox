#include "WorldGenerator.hpp"
#include <cmath>

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

int WorldGenerator::GetBlock(int X, int Y, int Z) {
    if (
            abs(X) > MAX_WORLD_SIZE ||
            abs(Y) > MAX_WORLD_SIZE ||
            abs(Z) > MAX_WORLD_SIZE) {
        return 1;
    }

    float fac = 0.;
    fac += _per.Get(X * 0.05f, Y * 0.05f, Z * 0.05f);
    if (fac > 0.5f) {
        return 1;
    }
    return 0;
}
