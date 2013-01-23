#include "World.hpp"
#include "WorldGenerator.hpp"
#include "Chunk.hpp"

#include <cstdlib>
#include <iostream>
#include <functional>

using namespace vox::engine;
using namespace vox::engine::entity;

using glm::vec3;

World::World(ChunkProvider* Provider) : _cache(Provider),
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
    OnBlockSet(X, Y, Z, Val);
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
        tr->GetBlock(lx, ly, lz) = Val;
    }
}

void World::AddEntity(Entity* Ent) {
    OnAddEntity(Ent);
    _ents.push_back(Ent);
}

void World::Tick() {
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

}

/*
vec3 World::Unproject(vec3 V) {
    vox::ren::TransformationManager* man = _ren->GetTranslationManager();

    man->PushMatrix();

    vec3 cameraPos = _cam.GetPosition();
        
    man->Rotate(-_ren->_pitch, -_ren->_yaw, -_ren->_roll);
    man->Translate(-cameraPos.x, -cameraPos.y, -cameraPos.z);

    vec3 tr = man->Unproject(V);

    man->PopMatrix();

    return tr;
}
*/
