#ifndef _STATE_GAMESTATE_H_
#define _STATE_GAMESTATE_H_

#include "State.hpp"
#include "ren/RenderManager.hpp"
#include "ren/hud/HUD.hpp"

namespace vox {
    class App;

    namespace engine {
        class World;
    }

    namespace state {
        class Gamestate : public State {
            private:
                vox::engine::World* _world;
                vox::ren::RenderManager* _rman;
                vox::ren::hud::HUD* _hud;
                vox::engine::entity::PlayerEntity* _player;
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

                virtual void OnMouseClick(int Button, int X, int Y);
                virtual void OnMouseMove(const SDL_MouseMotionEvent& Motion);
        };
    }
}

#endif 
