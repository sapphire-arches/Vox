#include "RenderManager.hpp"
#include <GL/glew.h>

using namespace vox::ren;

RenderManager::RenderManager() {
}

RenderManager::~RenderManager() {
}

void RenderManager::EnterGameWorldRender() {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void RenderManager::LeaveGameWorldRender() {
    glDisable(GL_DEPTH_TEST);
}

void RenderManager::EnterHUDRender() {
    glClear(GL_DEPTH_BUFFER_BIT);
}

void RenderManager::LeaveHUDRender() {
    
}
