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
    }
}

void Gamestate::Enter(App& TheApp) {
    _world = new vox::engine::World();
}

void Gamestate::Leave(App& TheApp) {
    std::cout << "Leaving Gamestate" << std::endl;
    delete _world;
    _world = NULL;
}

void Gamestate::Render(App& TheApp) {
    _world->Render(*this);
}

void Gamestate::Tick(App& TheApp) {
    _world->Tick();
    ++_frame;
}
