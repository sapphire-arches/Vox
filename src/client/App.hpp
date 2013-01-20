#ifndef _APP_H_
#define _APP_H_
#include <SDL/SDL.h>

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
        public:
            App();

            int OnExecute(vox::state::State* First);

            bool OnInit(vox::state::State* First);
            void OnEvent(SDL_Event* Event);
            void OnLoop();
            void OnRender();
            void OnCleanup();

    };
}
#endif
