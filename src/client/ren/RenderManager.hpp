#ifndef _REN_RENDERMANAGER_H_
#define _REN_RENDERMANAGER_H_

#include <GL/glew.h>

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

                GLuint RenderBufferName;
                GLuint RenderTexture;
                GLuint DepthRenderBuffer;

                RenderManager();
                ~RenderManager();

                void EnterGameWorldRender();
                void LeaveGameWorldRender();

                void EnterHUDRender();
                void LeaveHUDRender();

                void OnResize(int w, int h);
        };
    }
}

#endif
