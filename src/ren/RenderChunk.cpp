#include "RenderChunk.hpp"
#include <vector>
#include <GL/glew.h>
#include <iostream>
#include <boost/static_assert.hpp>
#include <glm/glm.hpp>

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
            v[0].x = X + 1; v[0].y = Y + 0; v[0].z = Z + 1;
            v[1].x = X + 1; v[1].y = Y + 1; v[1].z = Z + 1;
            v[2].x = X + 0; v[2].y = Y + 1; v[2].z = Z + 1;
            v[3].x = X + 0; v[3].y = Y + 0; v[3].z = Z + 1;
            break;
        case NEGX:
            v[0].x = X + 0; v[0].y = Y + 0; v[0].z = Z + 1;
            v[1].x = X + 0; v[1].y = Y + 1; v[1].z = Z + 1;
            v[2].x = X + 0; v[2].y = Y + 1; v[2].z = Z + 0;
            v[3].x = X + 0; v[3].y = Y + 0; v[3].z = Z + 0;
            break;
        case NEGY:
            v[0].x = X + 1; v[0].y = Y + 0; v[0].z = Z + 0;
            v[1].x = X + 1; v[1].y = Y + 0; v[1].z = Z + 1;
            v[2].x = X + 0; v[2].y = Y + 0; v[2].z = Z + 1;
            v[3].x = X + 0; v[3].y = Y + 0; v[3].z = Z + 0;
            break;
        case NEGZ:
            v[0].x = X + 0; v[0].y = Y + 0; v[0].z = Z + 0;
            v[1].x = X + 0; v[1].y = Y + 1; v[1].z = Z + 0;
            v[2].x = X + 1; v[2].y = Y + 1; v[2].z = Z + 0;
            v[3].x = X + 1; v[3].y = Y + 0; v[3].z = Z + 0;
            break;
    }
    //Calc normals.
    glm::vec3 a(v[0].x , v[0].y, v[0].z);
    glm::vec3 b(v[1].x , v[1].y, v[1].z);
    glm::vec3 c(v[2].x , v[2].y, v[2].z);

    glm::vec3 norm = glm::cross(b - a, c - a);

    int basei = Verts.size();
    for (int i = 0; i < 4; ++i) {
        v[i].r = 1.f;//fabs(v[i].x / 16.0f);
        v[i].g = 1.f;//fabs(v[i].y / 16.0f);
        v[i].b = 1.f;//fabs(v[i].z / 16.0f);
        v[i].nx = norm.x;
        v[i].ny = norm.y;
        v[i].nz = norm.z;
        Verts.insert(Verts.end(), v[i]);
        Ind.insert(Ind.end(), basei + i);
    }
}

void BuildVox(int X, int Y, int Z, const World& In, std::vector<Vertex>& Verts, std::vector<int>& Ind) {
    if (In(X + 1, Y, Z) == 0)
        AddSquare(X, Y, Z,  POSX, Verts, Ind);
    if (In(X - 1, Y, Z) == 0)
        AddSquare(X, Y, Z,  NEGX, Verts, Ind);
    if (In(X, Y + 1, Z) == 0)
        AddSquare(X, Y, Z,  POSY, Verts, Ind);
    if (In(X, Y - 1, Z) == 0)
        AddSquare(X, Y, Z,  NEGY, Verts, Ind);
    if (In(X, Y, Z + 1) == 0)
        AddSquare(X, Y, Z,  POSZ, Verts, Ind);
    if (In(X, Y, Z - 1) == 0)
        AddSquare(X, Y, Z,  NEGZ, Verts, Ind);
}

RenderChunk::RenderChunk(int X, int Y, int Z, const World& For) {
    _x = X;
    _y = Y;
    _z = Z;

    std::vector<Vertex> verts;
    std::vector<int>    ind;

    int bx = X * CHUNK_SIZE;
    int by = Y * CHUNK_SIZE;
    int bz = Z * CHUNK_SIZE;
    for (int x = 0; x < CHUNK_SIZE; ++x) {
        //Global x
        int gx = x + bx;
        for (int y = 0; y < CHUNK_SIZE; ++y) {
            //Global y
            int gy = y + by;
            for (int z = 0; z < CHUNK_SIZE; ++z) {
                //Global Z
                int gz = z + bz;
                if (For(gx, gy, gz) != 0)
                    BuildVox(gx, gy, gz, For, verts, ind);
            }
        }
    }

    if (ind.size() > 0)
        _mesh = new Mesh(&ind[0], ind.size(), &verts[0], verts.size(), GL_QUADS);
    else
        _mesh = NULL;
}

RenderChunk::~RenderChunk() {
    delete _mesh;
}
