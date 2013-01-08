#include "WorldRenderer.hpp"
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/core/func_trigonometric.hpp>
#include "../engine/World.hpp"
#include "./gl/Shader.hpp"
#include "./gl/Util.hpp"

#include <iostream>

#define VIEWDIST 4

using namespace std;
using namespace vox::ren;
using namespace vox::ren::gl;
using namespace vox::engine;

static inline int GetInd(int X, int Y, int Z) {
    return X + Y * VIEWDIST + Z * VIEWDIST * VIEWDIST;
}

WorldRenderer::WorldRenderer(World& For) : 
    _for(For),
    _basic(*(new ShaderProgram())) {
    _chunks = new RenderChunk*[VIEWDIST * VIEWDIST * VIEWDIST];

    for (int x = 0; x < VIEWDIST; ++x) {
        for (int y = 0; y < VIEWDIST; ++y) {
            for (int z = 0; z < VIEWDIST; ++z) {
                _chunks[GetInd(x, y, z)] = new RenderChunk(x - 2, y - 2, z - 2, For);
            }
        }
    }

    string m("MView");
    string p("MProj");
    _mloc = _basic.GetUniformLoc(m);
    _ploc = _basic.GetUniformLoc(p);

    glPointSize(5.0f);
}

WorldRenderer::~WorldRenderer() {
    for (int i = 0; i < VIEWDIST * VIEWDIST * VIEWDIST; ++i) {
        delete _chunks[i];
    }
    delete[] _chunks;
}

void WorldRenderer::Render(vox::state::Gamestate& GS) {
    while (!_mStack.empty()) {
        _mStack.pop();
    }
    while (!_pStack.empty()) {
        _pStack.pop();
    }
    glm::mat4 proj = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

    float angle = GS.GetFrame() * 0.25f; //glm::sin(GS.GetFrame() * 0.01f) * 90 + 90;
//    std::cout << angle << std::endl;
    glm::mat4 view(1.0f);
    view = glm::translate(
            view, 
            glm::vec3(-0.f, -0.f, -20.f)
            );
    view = glm::rotate(
            view,
            0.f,
            glm::vec3(1.f, 0.f, 0.f));
    
    view = glm::rotate(
            view,
            angle,
            glm::vec3(0.f, 1.f, 0.f));
    view = glm::translate(
            view,
            glm::vec3(-0.f, -8.f, -0.f)
            );
    

    _mStack.push(view);
    _pStack.push(proj);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    PrintGLError("Prerender");
    _basic.Use();
    PrintGLError("WorldRenderer::Render");

    glEnable(GL_DEPTH_TEST);

    glUniformMatrix4fvARB(_ploc, 1, GL_FALSE, &_pStack.top()[0][0]);
    glUniformMatrix4fvARB(_mloc, 1, GL_FALSE, &_mStack.top()[0][0]);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
   
    for (int i = 0; i < VIEWDIST * VIEWDIST * VIEWDIST; ++i) {
        _chunks[i]->Render();
    }

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glDisable(GL_DEPTH_TEST);
    PrintGLError("Postrender");
    glFlush();
}
