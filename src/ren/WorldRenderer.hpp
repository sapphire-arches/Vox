#ifndef _REN_WORLD_RENDERER_H_INCLUDED_
#define _REN_WORLD_RENDERER_H_INCLUDED_

#include <stack>
#include <boost/static_assert.hpp>
#include <glm/glm.hpp>
#include "Mesh.hpp"
#include "RenderChunk.hpp"
#include "../state/GameState.hpp"

namespace vox {
    namespace engine {
        class World;
    }

    namespace ren {
        namespace gl {
            class ShaderProgram;
        }

        class WorldRenderer {
            public:
                WorldRenderer(vox::engine::World& For);
                ~WorldRenderer();
                void Render(vox::state::Gamestate& GS);
            private:
                vox::engine::World& _for;
                vox::ren::gl::ShaderProgram& _basic;
                std::stack<glm::mat4> _mStack;
                std::stack<glm::mat4> _pStack;
                int _mloc;
                int _ploc;
                vox::ren::RenderChunk* _chunk;
        };
    }
}
#endif
