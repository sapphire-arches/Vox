#ifndef _APP_H_
#define _APP_H_
#include <SDL/SDL.h>
#include "engine/Stat.hpp"

namespace vox {
    namespace state {
        class State;
    }

    class App {
        private:
            bool _running;
            SDL_Surface* _surface;
            vox::state::State* _curr;

            int _mouseX;
            int _mouseY;

            vox::engine::Stat<int> _frameTime;
        public:
            App();

            int OnExecute(vox::state::State* First);

            bool OnInit(vox::state::State* First);
            void OnEvent(SDL_Event* Event);
            void OnLoop();
            void OnRender();
            void OnCleanup();

            inline vox::engine::Stat<int> GetFrameTime() {
                return _frameTime;
            }

            inline int GetFrame() {
                return _frameTime.Count;
            }
    };
}
#endif
