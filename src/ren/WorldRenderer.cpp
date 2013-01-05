#include <boost/static_assert.hpp>
#include <glm/glm.hpp>

#include <GL/glew.h>
#include <GL/gl.h>
#include "WorldRenderer.hpp"
#include "../engine/World.hpp"
#include "./gl/Shader.hpp"
#include "./gl/Util.hpp"

#include <iostream>

using namespace std;
using namespace vox::ren;
using namespace vox::ren::gl;
using namespace vox::engine;

WorldRenderer::WorldRenderer(World& For) : 
    _for(For),
    _basic(*(new ShaderProgram())) {
    int ind[4];
    ind[0] = 0; ind[1] = 1; ind[2] = 2; ind[3] = 3;
    Vertex verts[4];
    verts[0].x = -0.5f; verts[0].y = -0.5f;
    verts[1].x =  0.5f; verts[1].y = -0.5f;
    verts[2].x =  0.5f; verts[2].y =  0.5f;
    verts[3].x = -0.5f; verts[3].y =  0.5f;

    for(int i = 0; i < 4; ++i) {
        verts[i].r = verts[i].g = 1.0f;
        verts[i].b = 0.25f * i;
    }
    _flat = new Mesh(ind, 4, verts, 4, GL_QUADS);
}

WorldRenderer::~WorldRenderer() {
    delete _flat;
}

void WorldRenderer::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    PrintGLError("Prerender");
    _basic.Use();
    PrintGLError("WorldRenderer::Render");
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
   
    _flat->Render();

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    PrintGLError("Postrender");
    glFlush();
}
