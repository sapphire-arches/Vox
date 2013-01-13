#include "WorldRenderer.hpp"
#include <GL/glew.h>
#include "engine/World.hpp"
#include "./gl/Shader.hpp"
#include "./gl/Util.hpp"

#include <iostream>

#define VIEWDIST 10
#define HALFDIST (VIEWDIST / 2)

using namespace std;
using namespace vox::ren;
using namespace vox::ren::gl;
using namespace vox::engine;

static inline int GetInd(int X, int Y, int Z) {
    return X + Y * VIEWDIST + Z * VIEWDIST * VIEWDIST;
}

WorldRenderer::WorldRenderer(World& For) : 
    _for(For),
    _basic(*(new ShaderProgram())),
    _man(75.f, 4.f/3.f) {
    _chunks = new RenderChunk*[VIEWDIST * VIEWDIST * VIEWDIST];

    for (int x = 0; x < VIEWDIST; ++x) {
        for (int y = 0; y < VIEWDIST; ++y) {
            for (int z = 0; z < VIEWDIST; ++z) {
                _chunks[GetInd(x, y, z)] = new RenderChunk(x - HALFDIST, y - HALFDIST, z - HALFDIST, For);
            }
        }
    }

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

void WorldRenderer::Render(vox::state::Gamestate& GS) {

    float angle = GS.GetFrame() * 0.25;//glm::sin(GS.GetFrame() * 0.01f) * 90 + 90;
//    std::cout << angle << std::endl;
    
    _man.Translate(0., 0., -0.f);
    _man.Rotate(0.f, angle, 0.);
    _man.Translate(-0., -8., 0.);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    PrintGLError("Prerender");
    _basic.Use();
    PrintGLError("WorldRenderer::Render");

    _man.SetLocations(_mloc, _ploc);
    _man.ToGPU();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
   
    for (int i = 0; i < VIEWDIST * VIEWDIST * VIEWDIST; ++i) {
        _chunks[i]->Render();
    }

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    PrintGLError("Postrender");
    glFlush();
}

TransformationManager* WorldRenderer::GetTranslationManager() {
    return &_man;
}
