#include "RenderManager.hpp"
#include <GL/glew.h>

using namespace vox::ren;

RenderManager::RenderManager() {
}

RenderManager::~RenderManager() {
}

void RenderManager::EnterGameWorldRender() {
    //TODO: Implement
}

void RenderManager::LeaveGameWorldRender() {
    //TODO: Implement, undo whatever was done in RenderManager::EnterGameWorldRender();
}

void RenderManager::EnterHUDRender() {
    //Any setup/cleanup not here is done in ren/hud/HUD.cpp
}

void RenderManager::LeaveHUDRender() {
    //Any setup/cleanup not here is done in ren/hud/HUD.cpp
}
