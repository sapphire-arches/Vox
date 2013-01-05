#include "World.hpp"
#include <cstdlib>

#define SIZE 2 * CHUNK_SIZE

using namespace vox::engine;

World::World() {
    _data = new int[SIZE * SIZE * SIZE];
    for (int x = 0; x < SIZE; ++x) {
        for (int y = 0; y < SIZE; ++y) {
            for (int z = 0; z < SIZE; ++z) {
                (*this)(x, y, z) = (rand() % 4 == 1) ? 1 : 0;
            }
        }
    }
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
