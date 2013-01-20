#ifndef _REN_HUD_H_
#define _REN_HUD_H_

#include "engine/entity/PlayerEntity.hpp"
#include "ren/gl/Shader.hpp"

namespace vox {
    namespace ren {
        namespace hud {
            class HUD {
                private:
                    vox::engine::entity::PlayerEntity& _moniter;
                    vox::ren::gl::ShaderProgram _prog;

                    int _mloc;
                    int _ploc;

                    glm::mat4 _proj;
                    glm::mat4 _mview;
                    //Just like every other OpenGL interacting class, no copypasta.
                    HUD(const HUD& Other);
                    HUD& operator= (const HUD& Other);
                public:
                    HUD(vox::engine::entity::PlayerEntity& Moniter);
                    ~HUD();

                    void Render();
            };
        }
    }
}

#endif
