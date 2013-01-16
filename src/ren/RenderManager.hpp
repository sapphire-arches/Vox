#ifndef _REN_RENDERMANAGER_H_
#define _REN_RENDERMANAGER_H_

namespace vox {
    namespace ren {
        //Sets up FBOs etc. for different render mdoes.
        class RenderManager {
            private:

                //No CopyPasta, just like every other class in here that directly interacts with OGL
                RenderManager(const RenderManager& Other);
                RenderManager& operator= (const RenderManager& Other);
            public:
                //DATA
                int ScreenWidth;
                int ScreenHeight;


                RenderManager();
                ~RenderManager();

                void EnterGameWorldRender();
                void LeaveGameWorldRender();

                void EnterHUDRender();
                void LeaveHUDRender();
        };
    }
}

#endif
