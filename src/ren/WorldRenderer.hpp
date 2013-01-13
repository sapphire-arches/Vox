#ifndef _REN_WORLD_RENDERER_H_INCLUDED_
#define _REN_WORLD_RENDERER_H_INCLUDED_

#include <stack>
#include <boost/static_assert.hpp>
#include <glm/glm.hpp>

#include "Mesh.hpp"
#include "RenderChunk.hpp"
#include "TransformationManager.hpp"

#include "state/GameState.hpp"

namespace vox {
    namespace engine {
        class World;
    }

    namespace ren {
        namespace gl {
            class ShaderProgram;
        }

        class WorldRenderer {
            private:
                vox::engine::World& _for;
                vox::ren::gl::ShaderProgram& _basic;
                vox::ren::TransformationManager _man;
                int _mloc;
                int _ploc;
                vox::ren::RenderChunk** _chunks;
                glm::vec2 _cameraPos;
            public:
                WorldRenderer(vox::engine::World& For);
                ~WorldRenderer();

                void Render(vox::state::Gamestate& GS);

                void SetCameraPosition(float X, float Y);
                vox::ren::TransformationManager* GetTranslationManager();
        };
    }
}
#endif
