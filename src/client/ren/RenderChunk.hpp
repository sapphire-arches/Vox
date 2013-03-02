#ifndef _REN_RENDERCHUNK_H_
#define _REN_RENDERCHUNK_H_

#include "engine/World.hpp"
#include "Mesh.hpp"

namespace vox {
    namespace ren {
        class RenderChunk {
            private:
                int _x, _y, _z;
                int _lod;
                bool _dirty;
                vox::ren::Mesh* _mesh;
            public:
                RenderChunk(int X, int Y, int Z, int LOD, vox::engine::World& For);
                ~RenderChunk();

                inline void Render() {
                    if (_mesh)
                        _mesh->Render();
                }

                inline void MarkDirty() {
                    _dirty = true;
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

                inline bool IsDirty() {
                    return _dirty;
                }
                
                inline int GetLOD() {
                    return _lod;
                }
        };
    }
}

#endif
