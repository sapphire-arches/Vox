#include "State.hpp"
#include "../App.hpp"

using namespace vox;
using namespace vox::state;

State::State() : _next(NULL) {
}

State::State(State& Next) : _next(&Next) {
}

State::~State() {
    //Nothing to do here
}

void State::Enter(App& TheApp) {
}

void State::Leave(App& TheApp) {
}

void State::Render(App& TheApp) {
}

void State::Tick(App& TheApp) {
}

bool State::Finished() {
    return false;
}

State* State::GetNext() {
    return _next;
}

State& State::operator= (const State& rhs) {
    if (this != &rhs) {
        return *this;
    }

    _next = rhs._next;

    return *this;
}

void State::OnMouseClick(int Button, int X, int Y) {
}
