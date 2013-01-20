#include "GameState.hpp"
#include "App.hpp"
#include "engine/World.hpp"
#include "engine/entity/Rocket.hpp"
#include "ren/WorldRenderer.hpp"
#include "GraphicsDefs.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace vox;
using namespace vox::engine::entity;
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

void Gamestate::OnMouseClick(int Button, int X, int Y) {
    if (Button == 1) {
        //Whatever format makes this work...
        glm::vec3 cdir = _world->GetCamera().GetDirection();

        glm::vec4 dir(0., 0., 1., 0.);
        glm::mat4 trans(1.f);
        trans = glm::rotate(trans, (float)cdir.z, glm::vec3(0, 0, 1));
        trans = glm::rotate(trans, (float)cdir.x, glm::vec3(0, 1, 0));
        trans = glm::rotate(trans, (float)cdir.y, glm::vec3(1, 0, 0));
        dir = trans * dir;
        dir = -dir;
//        dir = dir / float(glm::sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z));
//        std::cout << "-----" << std::endl;
//        std::cout << cdir.x << " " << cdir.y << " " << cdir.z << std::endl;
//        std::cout << dir.x << " " << dir.y << " " << dir.z << " " << dir.w << std::endl;
//        std::cout << X << " " << Y << std::endl;
        glm::vec3 pos = _world->GetCamera().GetPosition();
        const float OFFSET = glm::sqrt(3);
        glm::vec3 off(glm::cos(cdir.x) * OFFSET, 0, glm::sin(cdir.x));
        //Position + offset to avoid clipping.
        Rocket* r = new Rocket(pos - glm::vec3(0.25, 0.25, 0.25), (glm::vec3(dir.x, dir.y, dir.z)), _world->GetPlayer());
        _world->AddEntity(r);
    }
}

void Gamestate::OnMouseMove(const SDL_MouseMotionEvent& Motion) {
    _world->GetCamera().OnMouseMove(Motion.x - (WIDTH / 2), Motion.y - (HEIGHT / 2));
}
