#include <iostream>
#include "App.hpp"
#include "state/GameState.hpp"

using namespace std;

int main (int argc, const char** argv) {
    vox::state::Gamestate* s = new vox::state::Gamestate();
    vox::App* app = new vox::App();

    int status = app->OnExecute(s);

    delete app;
    delete s;

    return status;
}
