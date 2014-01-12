#include "App.hpp"
#include "state/State.hpp"
#include <GL/glew.h>
#include <iostream>
#include "GraphicsDefs.hpp"
#include "platform/Timer.hpp"
#include <cstring>

using namespace std;
using namespace vox;
using namespace vox::state;

App::App() : _running(true), _curr(NULL) {
}

bool App::OnInit(State* First) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    if ((_surface = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_FULLSCREEN)) == NULL) {
        return false;
    }

    if (glewInit() != GLEW_OK) {
        cout << "GLEW init failed." << endl;
        return false;
    }

    if (true &&
            GLEW_ARB_shader_objects &&
            GLEW_ARB_vertex_shader &&
            GLEW_ARB_fragment_shader &&
            GLEW_ARB_framebuffer_object &&
            GLEW_ARB_vertex_buffer_object) {
        cout << "Everything supported!" << endl;
    } else {
        cout << "We are missing things =(" << endl;
        return false;
    }

    cout << "Everything is honky-dory! Begining magic." << endl;

    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0f);
    glViewport(0, 0, WIDTH, HEIGHT);

    _curr = First;

    First->Enter(*this);

    return true;
}

void App::OnEvent(SDL_Event* Event) {
    if (Event->type == SDL_QUIT) {
        _running = false;
    } else if (Event->type == SDL_KEYDOWN) {
        if (Event->key.keysym.sym == SDLK_ESCAPE)
            _running = false;
    } else if (Event->type == SDL_MOUSEBUTTONDOWN) {
        SDL_MouseButtonEvent ev = Event->button;
        _curr->OnMouseClick(ev.button, ev.x, ev.y);
    } else if (Event->type == SDL_MOUSEMOTION) {
        SDL_MouseMotionEvent ev = Event->motion;
        SDL_WarpMouse(WIDTH / 2, HEIGHT / 2);
        _curr->OnMouseMove(ev);
    }
}

void App::OnLoop() {
    _curr->Tick(*this);

    if (_curr->Finished()) {
        _curr->Leave(*this);
        _curr = _curr->GetNext();
        _curr->Enter(*this);
    }
}

void App::OnRender() {
    _curr->Render(*this);
    SDL_GL_SwapBuffers();
}

void App::OnCleanup() {
    SDL_Quit();
}

int App::OnExecute(State* First) {
    if (OnInit(First) == false) {
        return -1;
    }

    SDL_Event event;
    memset(&event, 0, sizeof(SDL_Event));
    
    unsigned int stime = 0;//vox::platform::CurrentTime();
    _frameTime.Current = _frameTime.Count = _frameTime.Average = _frameTime.Total = _frameTime.Min = 0;
    _frameTime.Max = 0xFFF;//Big number

    while (_running) {
        stime = vox::platform::CurrentTime();
        while (SDL_PollEvent(&event)) {
            OnEvent(&event);
        }

        OnLoop();
        OnRender();

        int etime = int(vox::platform::CurrentTime() - stime);
        _frameTime.Current = etime;
        _frameTime.Total += etime;
        _frameTime.Count++;
        if (etime < _frameTime.Min) {
            _frameTime.Min = etime;
        } else if (etime < _frameTime.Max) {
            _frameTime.Max = etime;
        }
        if (_frameTime.Count % 1000 == 0) {
            _frameTime.Min = 0xFFF;
            _frameTime.Max = 0;
        }
        if (_frameTime.Count % 60 == 0) {
            std::cout << "Average FPS: " << (1000000. / (_frameTime.Total / float(_frameTime.Count))) << std::endl;
        }
    }

    OnCleanup();

    return 0;
}
