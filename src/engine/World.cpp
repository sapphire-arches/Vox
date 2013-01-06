#include "World.hpp"
#include <cstdlib>
#include <iostream>

#define SIZE CHUNK_SIZE

using namespace vox::engine;

World::World() {
    _data = new int[SIZE * SIZE * SIZE];
    srand(0);
    for (int x = 0; x < SIZE; ++x) {
        for (int z = 0; z < SIZE; ++z) {
            int my = (z % 3 == 1) ? 5 : 4;
            for (int y = 0; y < my; ++y) {
                (*this)(x, y, z) = 1;//(rand() % 4 == 1) ? 1 : 0;
            }
        }
    }
}

World::~World() {
    delete[] _data;
}

//XXX:SUPERDUPERHAX
int ZERO = 0;

inline int GetIndex(int x, int y, int z) {
    if(true &&
            0 <= x && x < SIZE &&
            0 <= y && y < SIZE &&
            0 <= z && z < SIZE) {

        return x + (y * SIZE) + (z * SIZE * SIZE);
    }
    //std::cout << "Out of bounds: (" << x << ", " << y << " , " << z << ")" << std::endl;
    return -1;
}

int& World::operator() (int x, int y, int z) {
    int ind = GetIndex(x, y, z);
    if (ind == -1)
        return ZERO;
    return _data[ind];
}

int World::operator() (int x, int y, int z) const {
    int ind = GetIndex(x, y, z);
    if (ind == -1)
        return ZERO;
    return _data[ind];
}
