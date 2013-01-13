#include "World.hpp"
#include "WorldGenerator.hpp"
#include "Chunk.hpp"
#include "ren/WorldRenderer.hpp"
#include "ren/TransformationManager.hpp"

#include <cstdlib>
#include <iostream>
#include <functional>

using namespace vox::engine;
using namespace vox::engine::entity;

World::World() : _cache() {
    srand(0);
    _ren = new vox::ren::WorldRenderer(*this);
    this->AddEntity(new Entity(glm::vec3(0, 10, 0)));
    Entity* ent = new Entity(glm::vec3(0, 10, 10));
//    ent->ApplyForce(glm::vec3(0, 0, -0.1));
    this->AddEntity(ent);
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
    vox::ren::TransformationManager* man = _ren->GetTranslationManager();
    man->PushMatrix();
    _ren->Render(State);
    EntityListIterator it = _ents.begin();
    while (it != _ents.end()) {
        man->PushMatrix();
        (*it)->Render(man);
        man->PopMatrix();
        ++it;
    }
    man->PopMatrix();
}

void World::Tick() {
    EntityListIterator it = _ents.begin();
    Entity* ent = NULL;
    glm::vec3 grav(0, -0.001, 0.);
    while (it != _ents.end()) {
        ent = *it;
        ent->Tick(*this);
        ent->ApplyForce(grav * ent->GetMass());

        ++it;
    }

    //TODO: Implement collision detection/resolution
    for (EntityListIterator en1 = _ents.begin();
            en1 != _ents.end();
            ++en1) {
        EntityListIterator en2 = en1; 
        for (++en2;
                en2 != _ents.end();
                ++en2) {
            if ((*en1)->Intersects(**en2)){
                (*en1)->ResolveCollision(**en2);
           }
        }
    }
}
