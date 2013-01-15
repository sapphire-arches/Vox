#include "WorldGenerator.hpp"

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

int WorldGenerator::GetBlock(int X, int Y, int Z) {
    float fac =  Y * -0.05f;
    if (fac < -1)
        return 0;
    if (fac > 0)
        return 1;
    fac += _per.Get(X * 0.05f, Y * 0.05f, Z * 0.05f);
    if (fac > 0)
        return 1;
    return 0;
}
