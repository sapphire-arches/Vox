#include "World.hpp"
#include "WorldGenerator.hpp"
#include "Chunk.hpp"
#include "ren/WorldRenderer.hpp"
#include "ren/TransformationManager.hpp"

#include <SDL/SDL.h>
#include <cstdlib>
#include <iostream>
#include <functional>

using namespace vox::engine;
using namespace vox::engine::entity;

using glm::vec3;

World::World() : _cache(),
    _player(*(new PlayerEntity(vec3(0, 10, 0)))),
    _cam(vec3(-0, 10, 10), _player) {
    srand(0);
    _ren = new vox::ren::WorldRenderer(*this);
    this->AddEntity(&_cam.GetEnt());
    _cam.GetEnt().ApplyForce(vec3(-0.1, 0.0, 0.0));
//    Entity* ent = new Entity(vec3(0, 10, 10), vec3(1, 2, 1));
//    ent->ApplyForce(glm::vec3(0, 0, -0.1));
//    this->AddEntity(ent);
}

World::~World() {
    std::cout << "Deleted World." << std::endl;
    delete _ren;
}

unsigned char ZERO = 0;

unsigned char& World::operator() (int X, int Y, int Z) {
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

unsigned char World::operator() (int X, int Y, int Z) const {
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
    _ren->SetCameraPosition(_cam.GetPosition());
    //Yaw Pitch Roll order
    vec3 dir = _cam.GetDirection();
    _ren->SetCameraDirection(dir.x, dir.y, dir.z);
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
    glm::vec3 grav(0, -0.01, 0.);
    while (it != _ents.end()) {
        ent = *it;
        ent->Tick(*this);
        ent->ApplyForce(grav * ent->GetMass());

        ++it;
    }

    _cam.Tick(*this);

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

    //Key stuff.
    int numKeys;
    Uint8* keys = SDL_GetKeyState(&numKeys);

    const float MoveSpeed = 0.025;

    float camYaw = _cam.GetDirection().x;
    camYaw = glm::radians(camYaw);

    float xDir = 0;
    float zDir = 0;
    if (keys[SDLK_w]) {
        xDir -= glm::sin(camYaw);
        zDir -= glm::cos(camYaw);
    }
    if (keys[SDLK_s]) {
        xDir += glm::sin(camYaw);
        zDir += glm::cos(camYaw);
    }
    if (keys[SDLK_d]) {
        xDir += glm::sin(camYaw + glm::radians(90.f));
        zDir += glm::cos(camYaw + glm::radians(90.f));
    }
    if (keys[SDLK_a]) {
        xDir -= glm::sin(camYaw + glm::radians(90.f));
        zDir -= glm::cos(camYaw + glm::radians(90.f));
    }
    if (keys[SDLK_SPACE]) {
        _player.Jetpack();
    }
    if (xDir * xDir + zDir * zDir > MoveSpeed * MoveSpeed) {
        float len = glm::sqrt(xDir * xDir + zDir * zDir);
        float fac = 1 / len * MoveSpeed;
        xDir *= fac;
        zDir *= fac;
    }
    _player.ApplyForce(glm::vec3(xDir, 0, zDir));
    _player._yaw = glm::degrees(camYaw);
}

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
