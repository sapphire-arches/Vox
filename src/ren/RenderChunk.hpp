#ifndef _REN_RENDERCHUNK_H_
#define _REN_RENDERCHUNK_H_

#include "../engine/World.hpp"
#include "Mesh.hpp"

namespace vox {
    namespace ren {
        class RenderChunk {
            private:
                int _x, _y, _z;
                vox::ren::Mesh* _mesh;
            public:
                RenderChunk(int X, int Y, int Z, const vox::engine::World& For);
                ~RenderChunk();

                inline void Render() {
                    if (_mesh)
                        _mesh->Render();
                }

                inline int GetX() {
                    return _x;
                }

                inline int GetY() {
                    return _y;
                }

                inline int GetZ() {
                    return _z;
                }
        };
    }
}

#endif
