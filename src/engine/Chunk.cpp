#include "Chunk.hpp"
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>

using namespace vox::engine;

Chunk::Chunk(int X, int Y, int Z) {
    std::cout << "Building chunk ("<<X<<","<<Y<<","<<Z<<")"<<std::endl;
    _x = X;
    _y = Y;
    _z = Z;
    _data = new int [CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
    memset(_data, 0, sizeof(int) * CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
//    memset(_data, 1, sizeof(int) * CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE / 2);
    for (int x = 0; x < CHUNK_SIZE; ++x) {
        int gx = x + X * CHUNK_SIZE;
        for (int y = 0; y < CHUNK_SIZE; ++y) {
            int gy = y + Y * CHUNK_SIZE;
            for (int z = 0; z < CHUNK_SIZE; ++z) {
                this->GetBlock(x, y, z) = (rand() % 4 == 1) ? 1 : 0;
            }
        }
    }
}

Chunk::Chunk(const Chunk& Other) {
    this->_data = new int [CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
    memcpy(this->_data, Other._data, sizeof(int) * CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
    this->_x = Other._x;
    this->_y = Other._y;
    this->_z = Other._z;
}

Chunk::~Chunk() {
    delete[] _data;
}

inline int GetInd(int X, int Y, int Z) {
    int ind = X + Y * CHUNK_SIZE + Z * CHUNK_SIZE * CHUNK_SIZE;
    assert(ind < (CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE));
    return ind;
}

int Chunk::GetBlock(int X, int Y, int Z) const {
    if (X < 0)
        X += CHUNK_SIZE;
    if (Y < 0)
        Y += CHUNK_SIZE;
    if (Z < 0)
        Z += CHUNK_SIZE;
    std::cout << _data [GetInd(X, Y, Z)] << std::endl;
    return _data[GetInd(X, Y, Z)];
}

int& Chunk::GetBlock(int X, int Y, int Z) {
    if (X < 0)
        X += CHUNK_SIZE;
    if (Y < 0)
        Y += CHUNK_SIZE;
    if (Z < 0)
        Z += CHUNK_SIZE;
    return _data[GetInd(X, Y, Z)];
}
