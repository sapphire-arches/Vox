#ifndef _REN_RENDERCHUNK_H_
#define _REN_RENDERCHUNK_H_

#include "../engine/World.hpp"
#include "Mesh.hpp"

namespace vox {
    namespace ren {
        class RenderChunk {
            public:
                RenderChunk(int X, int Y, int Z, vox::engine::World& For);
                ~RenderChunk();

                void Render();

                int GetX();
                int GetY();
                int GetZ();
            private:
                int _x, _y, _z;
                vox::ren::Mesh* _mesh;
        };
    }
}

#endif
