#ifndef _STATE_TESTINGSTATE_H_
#define _STATE_TESTINGSTATE_H_

#include "State.hpp"

namespace vox {
    class App;

    namespace engine {
        class World;
    }

    namespace ren {
        class WorldRenderer;
    }

    namespace state {
        class TestingState : public State {
            public:
                TestingState();
                ~TestingState();

                virtual void Enter(App& TheApp);
                virtual void Leave(App& TheApp);
                virtual void Render(App& TheApp);
                virtual void Tick(App& TheApp);
            private:
                vox::engine::World* _world;
                vox::ren::WorldRenderer* _renderer;
        };
    }
}
 
#endif
