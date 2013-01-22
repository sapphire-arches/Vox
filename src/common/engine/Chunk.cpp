#include "Chunk.hpp"
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace vox::engine;

static inline int GetInd(int X, int Y, int Z) {
    int ind = X + (Y * CHUNK_SIZE) + (Z * CHUNK_SIZE * CHUNK_SIZE);
    assert(ind < (CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE));
    return ind;
}

Chunk::Chunk(int X, int Y, int Z, unsigned char* Data) {
//    std::cout << "Building chunk ("<<X<<","<<Y<<","<<Z<<")"<<std::endl;
    _x = X;
    _y = Y;
    _z = Z;
    _data = new Block [CHUNK_BLOCKS];
    memcpy(Data, _data, CHUNK_BLOCKS * sizeof(Block));
}

//Warning: slow as shit.
Chunk::Chunk(const Chunk& Other) {
    this->_data = new Block [CHUNK_BLOCKS];
    memcpy(this->_data, Other._data, sizeof(Block) * CHUNK_BLOCKS);
    this->_x = Other._x;
    this->_y = Other._y;
    this->_z = Other._z;
}

Chunk::~Chunk() {
    delete[] _data;
}

Block Chunk::GetBlock(int X, int Y, int Z) const {
    if (X < 0)
        X += CHUNK_SIZE;
    if (Y < 0)
        Y += CHUNK_SIZE;
    if (Z < 0)
        Z += CHUNK_SIZE;
    std::cout << _data [GetInd(X, Y, Z)] << std::endl;
    return _data[GetInd(X, Y, Z)];
}

Block& Chunk::GetBlock(int X, int Y, int Z) {
    if (X < 0)
        X += CHUNK_SIZE;
    if (Y < 0)
        Y += CHUNK_SIZE;
    if (Z < 0)
        Z += CHUNK_SIZE;
    assert(X <= CHUNK_SIZE && Y <= CHUNK_SIZE && Z <= CHUNK_SIZE);
    return _data[GetInd(X, Y, Z)];
}
