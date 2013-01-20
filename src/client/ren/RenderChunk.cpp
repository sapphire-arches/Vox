#include "RenderChunk.hpp"
#include <vector>
#include <GL/glew.h>
#include <iostream>
#include <boost/static_assert.hpp>
#include <glm/glm.hpp>

using namespace vox::ren;
using namespace vox::engine;

//COLOR DEFINITIONS
static float Colors[][3] = {
    {0.0, 0.0, 0.0},
    {0.9, 0.9, 0.9},
    {0.4, 0.9, 0.4},
    {1.0, 0.0, 1.0},
};
//END COLOR DEFINITIONS.

enum Side {
    POSX,
    POSY,
    POSZ,
    NEGX,
    NEGY,
    NEGZ
};

static void AddSquare(float X, float Y, float Z, int Size, int ID, Side S, std::vector<Vertex>& Verts, std::vector<int>& Ind) {
    Vertex v[4];
    switch (S) {
        case POSX:
            v[0].x = X + Size; v[0].y = Y + 0   ; v[0].z = Z + 0;
            v[1].x = X + Size; v[1].y = Y + Size; v[1].z = Z + 0;
            v[2].x = X + Size; v[2].y = Y + Size; v[2].z = Z + Size;
            v[3].x = X + Size; v[3].y = Y + 0   ; v[3].z = Z + Size;
            break;
        case POSY:
            v[0].x = X + 0   ; v[0].y = Y + Size; v[0].z = Z + 0;
            v[1].x = X + 0   ; v[1].y = Y + Size; v[1].z = Z + Size;
            v[2].x = X + Size; v[2].y = Y + Size; v[2].z = Z + Size;
            v[3].x = X + Size; v[3].y = Y + Size; v[3].z = Z + 0;
            break;
        case POSZ:
            v[0].x = X + Size; v[0].y = Y + 0   ; v[0].z = Z + Size;
            v[1].x = X + Size; v[1].y = Y + Size; v[1].z = Z + Size;
            v[2].x = X + 0   ; v[2].y = Y + Size; v[2].z = Z + Size;
            v[3].x = X + 0   ; v[3].y = Y + 0   ; v[3].z = Z + Size;
            break;
        case NEGX:
            v[0].x = X + 0   ; v[0].y = Y + 0   ; v[0].z = Z + Size;
            v[1].x = X + 0   ; v[1].y = Y + Size; v[1].z = Z + Size;
            v[2].x = X + 0   ; v[2].y = Y + Size; v[2].z = Z + 0;
            v[3].x = X + 0   ; v[3].y = Y + 0   ; v[3].z = Z + 0;
            break;
        case NEGY:
            v[0].x = X + Size; v[0].y = Y + 0   ; v[0].z = Z + 0;
            v[1].x = X + Size; v[1].y = Y + 0   ; v[1].z = Z + Size;
            v[2].x = X + 0   ; v[2].y = Y + 0   ; v[2].z = Z + Size;
            v[3].x = X + 0   ; v[3].y = Y + 0   ; v[3].z = Z + 0;
            break;
        case NEGZ:
            v[0].x = X + 0   ; v[0].y = Y + 0   ; v[0].z = Z + 0;
            v[1].x = X + 0   ; v[1].y = Y + Size; v[1].z = Z + 0;
            v[2].x = X + Size; v[2].y = Y + Size; v[2].z = Z + 0;
            v[3].x = X + Size; v[3].y = Y + 0   ; v[3].z = Z + 0;
            break;
    }
    //Calc normals.
    glm::vec3 a(v[0].x , v[0].y, v[0].z);
    glm::vec3 b(v[1].x , v[1].y, v[1].z);
    glm::vec3 c(v[2].x , v[2].y, v[2].z);

    glm::vec3 norm = glm::cross(b - a, c - a);

    int basei = Verts.size();
    for (int i = 0; i < 4; ++i) {
        v[i].r = Colors[ID][0];//0.5f;//fabs(v[i].y / 16.0f);
        v[i].g = Colors[ID][1];// 1.f;//fabs(v[i].y / 16.0f);
        v[i].b = Colors[ID][2];//0.5f;//fabs(v[i].y / 16.0f);
        v[i].nx = norm.x;
        v[i].ny = norm.y;
        v[i].nz = norm.z;
        Verts.insert(Verts.end(), v[i]);
        Ind.insert(Ind.end(), basei + i);
    }
}

static void BuildVox(int X, int Y, int Z, int Size, World& In, std::vector<Vertex>& Verts, std::vector<int>& Ind) {
    int id = In.GetBlock(X, Y, Z);
    if (In.GetBlock(X + Size, Y, Z) == 0)
        AddSquare(X, Y, Z, Size, id, POSX, Verts, Ind);
    if (In.GetBlock(X - Size, Y, Z) == 0)
        AddSquare(X, Y, Z, Size, id, NEGX, Verts, Ind);
    if (In.GetBlock(X, Y + Size, Z) == 0)
        AddSquare(X, Y, Z, Size, id, POSY, Verts, Ind);
    if (In.GetBlock(X, Y - Size, Z) == 0)
        AddSquare(X, Y, Z, Size, id, NEGY, Verts, Ind);
    if (In.GetBlock(X, Y, Z + Size) == 0)
        AddSquare(X, Y, Z, Size, id, POSZ, Verts, Ind);
    if (In.GetBlock(X, Y, Z - Size) == 0)
        AddSquare(X, Y, Z, Size, id, NEGZ, Verts, Ind);
}

RenderChunk::RenderChunk(int X, int Y, int Z, int LOD, World& For) {
    _x = X;
    _y = Y;
    _z = Z;
    _lod = LOD;

    std::vector<Vertex> verts;
    std::vector<int>    ind;

    int bx = X * CHUNK_SIZE;
    int by = Y * CHUNK_SIZE;
    int bz = Z * CHUNK_SIZE;
    int itr = CHUNK_SIZE / _lod;
    for (int x = 0; x < CHUNK_SIZE; x += itr) {
        //Global x
        int gx = x + bx;
        for (int y = 0; y < CHUNK_SIZE; y += itr) {
            //Global y
            int gy = y + by;
            for (int z = 0; z < CHUNK_SIZE; z += itr) {
                //Global Z
                int gz = z + bz;
                if (For.GetBlock(gx, gy, gz) != 0) {
                    BuildVox(gx, gy, gz, itr, For, verts, ind);
                }
            }
        }
    }

    if (ind.size() > 0)
        _mesh = new Mesh(&ind[0], ind.size(), &verts[0], verts.size(), GL_QUADS);
    else
        _mesh = NULL;
    _dirty = false;

}

RenderChunk::~RenderChunk() {
    delete _mesh;
}
