#include "RenderChunk.hpp"
#include <vector>
#include <GL/glew.h>

using namespace vox::ren;
using namespace vox::engine;

enum Side {
    POSX,
    POSY,
    POSZ,
    NEGX,
    NEGY,
    NEGZ
};

void AddSquare(float X, float Y, float Z, Side S, std::vector<Vertex>& Verts, std::vector<int>& Ind) {
    Vertex v[4];
    switch (S) {
        case POSX:
            v[0].x = X + 1; v[0].y = Y + 0; v[0].z = Z + 0;
            v[1].x = X + 1; v[1].y = Y + 1; v[1].z = Z + 0;
            v[2].x = X + 1; v[2].y = Y + 1; v[2].z = Z + 1;
            v[3].x = X + 1; v[3].y = Y + 0; v[3].z = Z + 1;
            break;
        case POSY:
            v[0].x = X + 0; v[0].y = Y + 1; v[0].z = Z + 0;
            v[1].x = X + 0; v[1].y = Y + 1; v[1].z = Z + 1;
            v[2].x = X + 1; v[2].y = Y + 1; v[2].z = Z + 1;
            v[3].x = X + 1; v[3].y = Y + 1; v[3].z = Z + 0;
            break;
        case POSZ:
            v[0].x = X + 0; v[0].y = Y + 0; v[0].z = Z + 1;
            v[1].x = X + 0; v[1].y = Y + 1; v[1].z = Z + 1;
            v[2].x = X + 1; v[2].y = Y + 1; v[2].z = Z + 1;
            v[3].x = X + 1; v[3].y = Y + 0; v[3].z = Z + 1;
            break;
        case NEGX:
            v[0].x = X + 0; v[0].y = Y + 0; v[0].z = Z + 0;
            v[1].x = X + 0; v[1].y = Y + 1; v[1].z = Z + 0;
            v[2].x = X + 0; v[2].y = Y + 1; v[2].z = Z + 1;
            v[3].x = X + 0; v[3].y = Y + 0; v[3].z = Z + 1;
            break;
        case NEGY:
            v[0].x = X + 0; v[0].y = Y + 0; v[0].z = Z + 0;
            v[1].x = X + 0; v[1].y = Y + 0; v[1].z = Z + 1;
            v[2].x = X + 1; v[2].y = Y + 0; v[2].z = Z + 1;
            v[3].x = X + 1; v[3].y = Y + 0; v[3].z = Z + 0;
            break;
        case NEGZ:
            v[0].x = X + 0; v[0].y = Y + 0; v[0].z = Z + 0;
            v[1].x = X + 0; v[1].y = Y + 1; v[1].z = Z + 0;
            v[2].x = X + 1; v[2].y = Y + 1; v[2].z = Z + 0;
            v[3].x = X + 1; v[3].y = Y + 0; v[3].z = Z + 0;
            break;
    }
    v[0].r = 1; v[0].g = 0; v[0].b = 0;
    v[1].r = 0; v[1].g = 1; v[1].b = 0;
    v[2].r = 0; v[2].g = 0; v[2].b = 1;
    v[3].r = 1; v[3].g = 0; v[3].b = 1;
    int basei = Verts.size();
    for (int i = 0; i < 4; ++i) {
        Verts.insert(Verts.end(), v[i]);
        Ind.insert(Ind.end(), basei + i);
    }
}

void BuildVox(int X, int Y, int Z, World& In, std::vector<Vertex>& Verts, std::vector<int>& Ind) {
    int baseInd = Verts.size();
    if (In(X + 1, Y + 0, Z + 0) != 0) {
        AddSquare(X, Y, Z,  POSX, Verts, Ind);
    }
    if (In(X - 1, Y + 0, Z + 0) != 0) {
        AddSquare(X, Y, Z,  NEGX, Verts, Ind);
    }
    if (In(X + 0, Y + 1, Z + 0) != 0) {
        AddSquare(X, Y, Z,  POSY, Verts, Ind);
    }
    if (In(X + 0, Y - 1, Z + 0) != 0) {
        AddSquare(X, Y, Z,  NEGY, Verts, Ind);
    }
    if (In(X + 0, Y + 0, Z + 1) != 0) {
        AddSquare(X, Y, Z,  POSZ, Verts, Ind);
    }
    if (In(X + 0, Y + 0, Z - 1) != 0) {
        AddSquare(X, Y, Z,  NEGZ, Verts, Ind);
    }
}

RenderChunk::RenderChunk(int X, int Y, int Z, World& For) {
    _x = X;
    _y = Y;
    _z = Z;

    std::vector<Vertex> verts;
    std::vector<int>    ind;

    for (int x = 0; x < CHUNK_SIZE; ++x) {
        //Global x
        int gx = x + X * CHUNK_SIZE;
        for (int y = 0; y < CHUNK_SIZE; ++y) {
            //Global y
            int gy = y + Y * CHUNK_SIZE;
            for (int z = 0; z < CHUNK_SIZE; ++z) {
                //Global Z
                int gz = z + Z * CHUNK_SIZE;
                BuildVox(gx, gy, gz, For, verts, ind);
            }
        }
    }

    _mesh = new Mesh(&ind[0], ind.size(), &verts[0], verts.size(), GL_QUADS);
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
