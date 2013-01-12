#include "World.hpp"
#include "WorldGenerator.hpp"
#include "Chunk.hpp"
#include "ren/WorldRenderer.hpp"

#include <cstdlib>
#include <iostream>
#include <functional>

using namespace vox::engine;
using namespace vox::engine::entity;

World::World() : _cache() {
    srand(0);
    _ren = new vox::ren::WorldRenderer(*this);
    this->AddEntity(new Entity(glm::vec3(0, 0, 0)));
}

World::~World() {
}

int ZERO = 0;

int& World::operator() (int X, int Y, int Z) {
    int cx = X / CHUNK_SIZE;
    int cy = Y / CHUNK_SIZE;
    int cz = Z / CHUNK_SIZE;
    int lx = X % CHUNK_SIZE;
    int ly = Y % CHUNK_SIZE;
    int lz = Z % CHUNK_SIZE;

    if (X < 0 && lx != 0)
        --cx;
    if (Y < 0 && ly != 0)
        --cy;
    if (Z < 0 && lz != 0)
        --cz;
    
    return _cache.Get(cx, cy, cz).GetBlock(lx, ly, lz);
}

int World::operator() (int X, int Y, int Z) const {
    int cx = X / CHUNK_SIZE;
    int cy = Y / CHUNK_SIZE;
    int cz = Z / CHUNK_SIZE;
    int lx = X % CHUNK_SIZE;
    int ly = Y % CHUNK_SIZE;
    int lz = Z % CHUNK_SIZE;

    if (X < 0 && lx != 0)
        --cx;
    if (Y < 0 && ly != 0)
        --cy;
    if (Z < 0 && lz != 0)
        --cz;
    
    return _cache.Get(cx, cy, cz).GetBlock(lx, ly, lz);
}

void World::AddEntity(Entity* Ent) {
    _ents.push_back(Ent);
}

void World::Render(vox::state::Gamestate& State) {
    _ren->Render(State);
    EntityList::iterator it = _ents.begin();
    while (it != _ents.end()) {
        (*it)->Render();
        ++it;
    }
}

void World::Tick() {
    EntityList::iterator it = _ents.begin();
    while (it != _ents.end()) {
        (*it)->Tick(*this);
        ++it;
    }
}
