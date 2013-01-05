#include <iostream>
#include "App.hpp"
#include "state/TestingState.hpp"

using namespace std;

int main (int argc, const char** argv) {
    vox::state::TestingState* s = new vox::state::TestingState();
    vox::App* app = new vox::App();

    int status = app->OnExecute(s);

    delete app;

    return status;
}
