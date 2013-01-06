#include "GameState.hpp"
#include "../App.hpp"
#include "../ren/WorldRenderer.hpp"
#include "../engine/World.hpp"
#include <iostream>

using namespace vox;
using namespace vox::state;

Gamestate::Gamestate() : 
    State() {
}

Gamestate::~Gamestate() {
}

void Gamestate::Enter(App& TheApp) {
    _world = new vox::engine::World();
    _renderer = new vox::ren::WorldRenderer(*_world);
}

void Gamestate::Leave(App& TheApp) {
    std::cout << "Leaving Gamestate" << std::endl;
    delete _world;
    delete _renderer;
}

void Gamestate::Render(App& TheApp) {
    _renderer->Render(*this);
}

void Gamestate::Tick(App& TheApp) {
    ++_frame;
}
