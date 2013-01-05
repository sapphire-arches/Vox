#include "World.hpp"

#define SIZE 10

using namespace vox::engine;

World::World() {
    _data = new int[SIZE * SIZE * SIZE];
}

World::~World() {
    delete[] _data;
}

inline int& World::operator() (int x, int y, int z) {
    if(true &&
            0 < x && x < SIZE &&
            0 < y && y < SIZE &&
            0 < z && z < SIZE)
        return _data[x + y * SIZE + z * SIZE * SIZE];
    return _data[0];
}

inline int World::operator() (int x, int y, int z) const {
    return (*this)(x, y, z);
}
