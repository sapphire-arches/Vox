#include "GameState.hpp"
#include "App.hpp"
#include "engine/World.hpp"
#include <iostream>

using namespace vox;
using namespace vox::state;

Gamestate::Gamestate() : 
    State() {
}

Gamestate::~Gamestate() {
    if (_world != NULL) {
        std::cout << "Cleaning up!" << std::endl;
        delete _world;
        delete _rman;
        delete _hud;
    }
}

void Gamestate::Enter(App& TheApp) {
    _world = new vox::engine::World();
    _rman = new vox::ren::RenderManager();
    _player = &_world->GetPlayer();
    _hud = new vox::ren::hud::HUD(*_player);
}

void Gamestate::Leave(App& TheApp) {
    std::cout << "Leaving Gamestate" << std::endl;
    delete _world;
    delete _rman;
    delete _hud;
    _world = NULL;
}

void Gamestate::Render(App& TheApp) {
    _rman->EnterGameWorldRender();
    _world->Render(*this);
    _rman->LeaveGameWorldRender();

    _rman->EnterHUDRender();
    _hud->Render();
    _rman->LeaveHUDRender();
}

void Gamestate::Tick(App& TheApp) {
    _world->Tick();
    ++_frame;
}
