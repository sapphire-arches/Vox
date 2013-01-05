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
    _chunk = new RenderChunk(0, 0, 0, For);
}

WorldRenderer::~WorldRenderer() {
    delete _chunk;
}

void WorldRenderer::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    PrintGLError("Prerender");
    _basic.Use();
    PrintGLError("WorldRenderer::Render");
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
   
    _chunk->Render();

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    PrintGLError("Postrender");
    glFlush();
}
