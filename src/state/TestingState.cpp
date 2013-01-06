#include "TestingState.hpp"
#include "../App.hpp"
#include "../ren/WorldRenderer.hpp"
#include "../engine/World.hpp"
#include <iostream>

using namespace vox;
using namespace vox::state;

TestingState::TestingState() : 
    State() {
}

TestingState::~TestingState() {
}

void TestingState::Enter(App& TheApp) {
    _world = new vox::engine::World();
    _renderer = new vox::ren::WorldRenderer(*_world);
}

void TestingState::Leave(App& TheApp) {
    std::cout << "Leaving testing state" << std::endl;
    delete _world;
    delete _renderer;
}

void TestingState::Render(App& TheApp) {
    _renderer->Render(TheApp);
}

void TestingState::Tick(App& TheApp) {
}
