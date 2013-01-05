#include "RenderChunk.hpp"
#include <vector>

using namespace vox::ren;
using namespace vox::engine;

RenderChunk::RenderChunk(int X, int Y, int Z, World& For) {
    _x = X;
    _y = Y;
    _z = Z;

    std::vector<Vertex> verts;
    std::vector<int>    in;

    for (int x = 0; x < CHUNK_SIZE; ++x) {
        //Global x
        int gx = x + X * CHUNK_SIZE;
        for (int y = 0; y < CHUNK_SIZE; ++y) {
            //Global y
            int gy = y + Y * CHUNK_SIZE;
            for (int z = 0; z < CHUNK_SIZE; ++z) {
                //Global Z
                int gz = z + Z * CHUNK_SIZE;

            }
        }
    }
}

RenderChunk::~RenderChunk() {
    delete _mesh;
}

void RenderChunk::Render() {
    _mesh->Render();
}

int RenderChunk::GetX() {
    return _x;
}

int RenderChunk::GetY() {
    return _y;
}

int RenderChunk::GetZ() {
    return _z;
}
