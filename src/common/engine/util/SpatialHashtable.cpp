#include "SpatialHashtable.hpp"
#include <cstring>

using namespace vox::engine::util;

template <class T, int Size>
SpatialHashtable<T, Size>::SpatialHashtable() {
    _data = new T[Size * Size * Size];
    memset(_data, 0, Size * Size * Size * sizeof(T*));
}

template <class T, int Size>
SpatialHashtable<T, Size>::~SpatialHashtable() {
    for (int i = 0; i < Size * Size * Size; ++i) {
        if (_data[i] != NULL) {
            delete _data[i];
        }
    }
    delete[] _data;
}

template <class T, int Size>
T* SpatialHashtable<T, Size>::Get(int X, int Y, int Z) {
    int x = X % Size;
    int y = Y % Size;
    int z = Z % Size;
    if (x < 0) {
        x += Size;
    }
    if (y < 0) {
        y += Size;
    }
    if (z < 0) {
        z += Size;
    }
    return _data[x + y * Size + z * Size * Size];
}

template <class T, int Size>
void SpatialHashtable<T, Size>::Set(int X, int Y, int Z, T* Val) {
    int x = X % Size;
    int y = Y % Size;
    int z = Z % Size;
    if (x < 0) {
        x += Size;
    }
    if (y < 0) {
        y += Size;
    }
    if (z < 0) {
        z += Size;
    }
    _data[x + y * Size + z * Size * Size] = Val;
}
