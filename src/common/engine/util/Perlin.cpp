#include "Perlin.hpp"
#include <cstdlib>
#include <cstring>
#include "MathUtil.hpp"

#define SIZE 16
#define SIZE_CUBED (SIZE * SIZE * SIZE)

static inline int Ind(int X, int Y, int Z) {
    if (X == SIZE)
        X = 0;
    if (Y == SIZE)
        Y = 0;
    if (Z == SIZE)
        Z = 0;
    return X + Y * SIZE + Z * SIZE * SIZE;
}

using namespace vox::engine::util;

Perlin3D::Perlin3D(int Seed) {
    srand(Seed);
    _data = new float[SIZE_CUBED];    
    for (int i = 0; i < SIZE_CUBED; ++i) {
        _data[i] = (rand() / (float)(RAND_MAX));
    }
}

Perlin3D::Perlin3D(const Perlin3D& Other) {
    _data = new float[SIZE_CUBED];
    memcpy(_data, Other._data, SIZE_CUBED);
}

Perlin3D::~Perlin3D() {
    delete[] _data;
}

Perlin3D& Perlin3D::operator= (const Perlin3D& Other) {
    if (&Other == this)
        return *this;

    delete[] _data;
    _data = new float[SIZE_CUBED];
    memcpy(_data, Other._data, SIZE_CUBED);
    return *this;
}

static inline float Lerp(float F1, float F2, float F) {
    return F2 * F + F1 * (1 - F);
}

float Perlin3D::Get(float X, float Y, float Z) {
    int ix = vox::Floor(X);
    int iy = vox::Floor(Y);
    int iz = vox::Floor(Z);

    float fx = X - ix;
    float fy = Y - iy;
    float fz = Z - iz;

    //Correct indicies.
    ix %= SIZE;
    iy %= SIZE;
    iz %= SIZE;
    if (ix < 0)
        ix += SIZE;
    if (iy < 0)
        iy += SIZE;
    if (iz < 0)
        iz += SIZE;

    float temp[8];
    temp[0] = _data[Ind(ix + 0, iy + 0, iz + 0)];
    temp[1] = _data[Ind(ix + 0, iy + 0, iz + 1)];
    temp[2] = _data[Ind(ix + 0, iy + 1, iz + 0)];
    temp[3] = _data[Ind(ix + 0, iy + 1, iz + 1)];
    temp[4] = _data[Ind(ix + 1, iy + 0, iz + 0)];
    temp[5] = _data[Ind(ix + 1, iy + 0, iz + 1)];
    temp[6] = _data[Ind(ix + 1, iy + 1, iz + 0)];
    temp[7] = _data[Ind(ix + 1, iy + 1, iz + 1)];

    temp[0] = Lerp(temp[0], temp[1], fz);
    temp[1] = Lerp(temp[2], temp[3], fz);
    temp[2] = Lerp(temp[4], temp[5], fz);
    temp[3] = Lerp(temp[6], temp[7], fz);

    temp[0] = Lerp(temp[0], temp[1], fy);
    temp[1] = Lerp(temp[2], temp[3], fy);

    return Lerp(temp[0], temp[1], fx);
} 

#undef SIZE
#undef SIZE_CUBED
