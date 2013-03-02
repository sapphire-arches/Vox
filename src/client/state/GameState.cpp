#include "GameState.hpp"
#include "App.hpp"
#include "engine/World.hpp"
#include "engine/entity/Rocket.hpp"
#include "engine/NetworkListner.hpp"
#include "GraphicsDefs.hpp"
#include "platform/Timer.hpp"

#include <boost/asio.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace vox;
using namespace vox::engine::entity;
using namespace vox::state;
using namespace boost::asio::ip;

Gamestate::Gamestate() : 
    State() {
}

Gamestate::~Gamestate() {
    if (_world != NULL) {
        std::cout << "Cleaning up!" << std::endl;
        delete _world;
        delete _rman;
        delete _hud;
        delete _ren;
    }
}

void Gamestate::Enter(App& TheApp) {
    _skipFrame = false;
    _skipedFrames = 0;
    _simTime = 0;

    _world = new vox::engine::World();
    vox::engine::NetworkListner* prov =
        new vox::engine::NetworkListner(
                udp::endpoint(address::from_string("127.0.0.1"), 12090),
                *_world
                );
    _world->SetChunkProvider(prov);
    _ren = new vox::ren::WorldRenderer(*_world);
    _rman = new vox::ren::RenderManager();
    _player = new PlayerEntity(glm::vec3(0, 0, 0));
    _world->AddEntity(_player);
    _cam = new Camera(glm::vec3(0, 0, 0), *_player);
    _hud = new vox::ren::hud::HUD(*_player);
}

void Gamestate::Leave(App& TheApp) {
    std::cout << "Leaving Gamestate" << std::endl;
    delete _ren;
    delete _world;
    delete _rman;
    delete _hud;
    _world = NULL;
}

void Gamestate::Render(App& TheApp) {
    if (_skipedFrames > 5 || !_skipFrame) {
        _rman->EnterGameWorldRender();
        _ren->Render();
        _rman->LeaveGameWorldRender();
    
        _rman->EnterHUDRender();
        _hud->Render(this);
        _rman->LeaveHUDRender();

        _skipFrame = false;
        _skipedFrames = 0;
    } else {
        ++_skipedFrames;
    }
}

void Gamestate::Tick(App& TheApp) {
    if (_delta.Current > 1) {
        _delta.Current = 1;
        _skipFrame = true;
    } else if (_delta.Current <= 0) {
        _delta.Current = 1;
    }
    
    _world->Tick(_simTime);
    _ren->SetCameraPosition(_cam->GetPosition());
    glm::vec3 dir = _cam->GetDirection();
    _ren->SetCameraDirection(dir.x, dir.y, dir.z);

    _cam->Tick(*_world);
    //Key stuff.
    int numKeys;
    Uint8* keys = SDL_GetKeyState(&numKeys);

    const float MoveSpeed = 0.01;

    float camYaw = _cam->GetDirection().x;
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
        _player->Jetpack();
    }
    if (xDir * xDir + zDir * zDir > MoveSpeed * MoveSpeed) {
        float len = glm::sqrt(xDir * xDir + zDir * zDir);
        float fac = 1 / len * MoveSpeed;
        xDir *= fac;
        zDir *= fac;
    }
    _player->ApplyForce(glm::vec3(xDir, 0, zDir));
    _player->Yaw = glm::degrees(camYaw);

    vox::engine::Stat<int> frameTime = TheApp.GetFrameTime();
    _simTime += frameTime.Current;
    //We want 24 fps at least
    _delta.Current = frameTime.Current * (1 / 4.1667e7);
    _delta.Total += _delta.Current;
    ++_delta.Count;
    if (TheApp.GetFrame() % 1000 == 1) {
        _delta.Min = 100;
        _delta.Max = 0;
    }
    if (_delta.Current < _delta.Min) {
        _delta.Min = _delta.Current;
    } else if (_delta.Current > _delta.Max) {
        _delta.Max = _delta.Current;
    }
}

void Gamestate::OnMouseClick(int Button, int X, int Y) {
    if (Button == 1) {
        //Whatever format makes this work...
        glm::vec3 cdir = _cam->GetDirection();

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
        glm::vec3 pos = _cam->GetPosition();
        const float OFFSET = glm::sqrt(3.f);
        glm::vec3 off(glm::cos(cdir.x) * OFFSET, 0, glm::sin(cdir.x));
        //Position + offset to avoid clipping.
        Rocket* r = new Rocket(pos - glm::vec3(0.25, 0.25, 0.25), (glm::vec3(dir.x, dir.y, dir.z)), *_player);
        _world->AddEntity(r);
    }
}

void Gamestate::OnMouseMove(const SDL_MouseMotionEvent& Motion) {
    _cam->OnMouseMove(Motion.x - (WIDTH / 2), Motion.y - (HEIGHT / 2));
}
