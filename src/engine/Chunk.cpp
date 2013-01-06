#include "Chunk.hpp"
#include <iostream>
#include <cassert>
#include <cstring>

using namespace vox::engine;

Chunk::Chunk(int X, int Y, int Z) {
    std::cout << "Building chunk ("<<X<<","<<Y<<","<<Z<<")"<<std::endl;
    _x = X;
    _y = Y;
    _z = Z;
    _data = new int [CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int y = 0; y < CHUNK_SIZE; ++y) {
            for (int z = 0; z < CHUNK_SIZE; ++z) {
                if (y + Y * CHUNK_SIZE < 8)
                    this->GetBlock(x, y, z) = 1;
                else
                    this->GetBlock(x, y, z) = 0;
            }
        }
    }
}

Chunk::Chunk(const Chunk& Other) {
    this->_data = new int [CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
    memcpy(this->_data, Other._data, CHUNK_SIZE* CHUNK_SIZE * CHUNK_SIZE);
    this->_x = Other._x;
    this->_y = Other._y;
    this->_z = Other._z;
}

Chunk::~Chunk() {
    delete[] _data;
}

inline int GetID(int X, int Y, int Z) {
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
    return _data[GetID(X, Y, Z)];
}

int& Chunk::GetBlock(int X, int Y, int Z) {
    if (X < 0)
        X += CHUNK_SIZE;
    if (Y < 0)
        Y += CHUNK_SIZE;
    if (Z < 0)
        Z += CHUNK_SIZE;
    return _data[GetID(X, Y, Z)];
}
