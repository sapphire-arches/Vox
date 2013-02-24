#include "World.hpp"
#include "WorldGenerator.hpp"
#include "Chunk.hpp"

#include <cstdlib>
#include <iostream>
#include <functional>

using namespace vox::engine;
using namespace vox::engine::entity;

using glm::vec3;

World::World() : 
    _cache(),
    _ents() {
    srand(0);
}

World::~World() {
    std::cout << "Deleted World." << std::endl;
}

unsigned char ZERO = 0;

Block World::GetBlock(int X, int Y, int Z) {
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
    
    Chunk* tr = _cache.Get(cx, cy, cz);
    if (tr != NULL) {
        return tr->GetBlock(lx, ly, lz);
    }
    return 0;
}

void World::SetBlock(int X, int Y, int Z, Block Val) {
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
    
    Chunk* tr = _cache.Get(cx, cy, cz);
    if (tr != NULL) {
        Block& b = tr->GetBlock(lx, ly, lz);
        if (b != Val) {
            b = Val;
            OnBlockSet(X, Y, Z, Val);
        }
    }
}

void World::AddEntity(Entity* Ent) {
    OnAddEntity(Ent);
    _ents.push_back(Ent);
}

#define SIMTIME 7

void World::Tick(int& DT) {
    while (DT > SIMTIME) {
        EntityListIterator it = _ents.begin();
        Entity* ent = NULL;
        glm::vec3 grav(0, -0.01, 0.);
        while (it != _ents.end()) {
            ent = *it;
            EntityListIterator curr = it++;
            ent->Tick(*this);
            ent->ApplyForce(grav * ent->GetMass());

            if (ent->GetHealth() <= 0) {
                OnRemoveEntity(ent);
                delete ent;
                _ents.erase(curr);
            }
        }

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
        DT -= SIMTIME;
    }
}

void World::SetChunkProvider(ChunkProvider* Provider) {
    _cache.SetChunkProvider(Provider);
}
