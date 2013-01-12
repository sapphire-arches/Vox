#ifndef _STATE_GAMESTATE_H_
#define _STATE_GAMESTATE_H_

#include "State.hpp"

namespace vox {
    class App;

    namespace engine {
        class World;
    }

    namespace state {
        class Gamestate : public State {
            private:
                vox::engine::World* _world;
                int _frame;
            public:
                Gamestate();
                ~Gamestate();

                virtual void Enter(App& TheApp);
                virtual void Leave(App& TheApp);
                virtual void Render(App& TheApp);
                virtual void Tick(App& TheApp);

                inline int GetFrame() {
                    return _frame;
                }
        };
    }
}

#endif 
