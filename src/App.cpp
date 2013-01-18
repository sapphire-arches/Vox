#include "App.hpp"
#include "state/State.hpp"
#include <GL/glew.h>
#include <iostream>
#include "GraphicsDefs.hpp"

using namespace std;
using namespace vox;
using namespace vox::state;

App::App() : _running(true), _curr(NULL) {
}

bool App::OnInit(State* First) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    if ((_surface = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_OPENGL | SDL_GL_DOUBLEBUFFER)) == NULL) {
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

    while (_running) {
        while (SDL_PollEvent(&event)) {
            OnEvent(&event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}
