#include "WorldRenderer.hpp"
#include <GL/glew.h>
#include "platform/Timer.hpp"
#include "engine/World.hpp"
#include "./gl/Shader.hpp"
#include "./gl/Util.hpp"
#include <cstring>
#include <list>

#include <iostream>

#define VIEWDIST 8
#define HALFDIST (VIEWDIST / 2)

using namespace std;
using namespace vox::ren;
using namespace vox::ren::gl;
using namespace vox::engine;

static inline int GetInd(int X, int Y, int Z) {
    int x = X % VIEWDIST;
    if (x < 0)
        x += VIEWDIST;
    int y = Y % VIEWDIST;
    if (y < 0)
        y += VIEWDIST;
    int z = Z % VIEWDIST;
    if (z < 0)
        z += VIEWDIST;
    return x + y * VIEWDIST + z * VIEWDIST * VIEWDIST;
}

WorldRenderer::WorldRenderer(World& For) : 
    _for(For),
    _basic(*(new ShaderProgram("res/base.frag", "res/base.vert"))),
    _man(75.f, 4.f/3.f),
    _cameraPos(0, 24, 0) {
    _chunks = new RenderChunk*[VIEWDIST * VIEWDIST * VIEWDIST];

    memset(_chunks, (int)NULL, VIEWDIST * VIEWDIST * VIEWDIST * sizeof(RenderChunk*));

    string m("MView");
    string p("MProj");
    _mloc = _basic.GetUniformLoc(m);
    _ploc = _basic.GetUniformLoc(p);

    _man.SetLocations(_mloc, _ploc);

    glPointSize(5.0f);
    glEnable(GL_DEPTH_TEST);
}

WorldRenderer::~WorldRenderer() {
    for (int i = 0; i < VIEWDIST * VIEWDIST * VIEWDIST; ++i) {
        delete _chunks[i];
    }
    delete[] _chunks;
}

static inline int ManhatanDistance(int x1, int y1, int z1, int x2, int y2, int z2) {
    return
        abs(x1 - x2) +
        abs(y1 - y2) +
        abs(z1 - z2);
}
//
//static int Floor (float F) {
//    if (F < 0)
//        return (int)F -1;
//    return (int)F;
//}
//
void WorldRenderer::Render(vox::state::Gamestate& GS) {
    float angle = GS.GetFrame() * 0.25;//glm::sin(GS.GetFrame() * 0.01f) * 90 + 90;
//    std::cout << angle << std::endl;
   
//    _cameraPos.x = GS.GetFrame() / 16.f;
    _man.Rotate(-_pitch, -_yaw, -_roll);
    _man.Translate(-_cameraPos.x, -_cameraPos.y, -_cameraPos.z);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    PrintGLError("Prerender");
    _basic.Use();
    PrintGLError("WorldRenderer::Render");

    _man.SetLocations(_mloc, _ploc);
    _man.ToGPU();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    unsigned int stime = vox::platform::CurrentTime(); 
    unsigned int elapsed = 0;
    for (int x = 0; x < VIEWDIST; ++x) {
        for (int y = 0; y < VIEWDIST; ++y) {
            for (int z = 0; z < VIEWDIST; ++z) {
                int cx = x + int(_cameraPos.x / CHUNK_SIZE) - HALFDIST;
                int cy = y + int(_cameraPos.y / CHUNK_SIZE) - HALFDIST;
                int cz = z + int(_cameraPos.z / CHUNK_SIZE) - HALFDIST;
                int magic = ManhatanDistance(x, y, z, HALFDIST, HALFDIST, HALFDIST) - 5;
                if (magic < 0)
                    magic = 0;
                int lod = CHUNK_SIZE >> magic;
                if (lod == 0)
                    lod = 1;
                int ind = GetInd(cx, cy, cz);
                RenderChunk* curr = _chunks[ind];
                if (curr == NULL) {
                    ToBuildChunk temp;
                    temp.X = cx;
                    temp.Y = cy;
                    temp.Z = cz;
                    temp.LOD = lod;
                    temp.Ind = ind;
                    temp.Parent = this;
                    _toBuild.insert(temp);
                    curr = NULL;
                } else if (
                        curr->GetLOD() != lod ||
                        curr->GetX() != cx ||
                        curr->GetY() != cy ||
                        curr->GetZ() != cz) {
                    ToBuildChunk temp;
                    temp.X = cx;
                    temp.Y = cy;
                    temp.Z = cz;
                    temp.LOD = lod;
                    temp.Ind = ind;
                    temp.Parent = this;
                    _toBuild.insert(temp);
                }
                if (curr != NULL)
                    curr->Render();
                elapsed = vox::platform::CurrentTime() - stime;
                //8ms
#ifndef VALGRIND
                if (elapsed > 8000) {
                    goto bail;
                }
#endif
            }
        }
    }
bail:
    //XXX:This prevents valgrind from letting me profile the game. To slow...
    if (!_toBuild.empty()) {
        ToBuildSet::iterator it = _toBuild.begin();
        while (
#ifndef VALGRIND
                elapsed < 8000 &&
#endif
                it != _toBuild.end()) {
            ToBuildChunk c = *it;
            ToBuildSet::iterator curr = it++;
            _toBuild.erase(curr);
            delete _chunks[c.Ind];
            _chunks[c.Ind] = NULL;
            _chunks[c.Ind] = new RenderChunk(c.X, c.Y, c.Z, c.LOD, _for);
            elapsed = vox::platform::CurrentTime() - stime;
        }
    }

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    PrintGLError("Postrender");
    glFlush();
}

TransformationManager* WorldRenderer::GetTranslationManager() {
    return &_man;
}

void WorldRenderer::SetCameraPosition(glm::vec3 Vec) {
    _cameraPos = Vec;
}

void WorldRenderer::SetCameraDirection(float Yaw, float Pitch, float Roll) {
    _yaw = Yaw;
    _pitch = Pitch;
    _roll = Roll;
}

//----------------------------------
//      ToBuildChunk Members.
//----------------------------------

bool ToBuildChunk::operator< (const ToBuildChunk& Other) const {
    //Positions must be in chunk coords.
    float camx = Parent->_cameraPos.x / CHUNK_SIZE;
    float camy = 1;
    float camz = Parent->_cameraPos.y / CHUNK_SIZE;

    return ManhatanDistance(X, Y, Z, camx, camy, camz) <
        ManhatanDistance(Other.X, Other.Y, Other.Z, camx, camy, camz);
}
