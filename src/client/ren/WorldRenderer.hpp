#ifndef _REN_WORLD_RENDERER_H_INCLUDED_
#define _REN_WORLD_RENDERER_H_INCLUDED_

#include <stack>
#include <set>
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

        struct ToBuildChunk {
            int X, Y, Z, LOD, Ind;
            WorldRenderer* Parent;

            bool operator= (const ToBuildChunk& Other) const{
                return 
                    X == Other.X &&
                    Y == Other.Y &&
                    Z == Other.Z &&
                    LOD == Other.LOD &&
                    Ind == Other.Ind;
            }

            bool operator< (const ToBuildChunk& Other) const;
        };

        typedef std::set<ToBuildChunk> ToBuildSet;

        class WorldRenderer {
            private:
                vox::engine::World& _for;
                vox::ren::gl::ShaderProgram& _basic;
                vox::ren::TransformationManager _man;
                int _mloc;
                int _ploc;
                vox::ren::RenderChunk** _chunks;
                glm::vec3 _cameraPos;
                ToBuildSet _toBuild;
                friend ToBuildChunk;
            public:
                float _yaw, _pitch, _roll;
                WorldRenderer(vox::engine::World& For);
                ~WorldRenderer();

                void Render(vox::state::Gamestate& GS);

                void SetCameraPosition(float X, float Y, float Z);
                void SetCameraPosition(glm::vec3 Vec);
                void SetCameraDirection(float Yaw, float Pitch, float Roll);
                vox::ren::TransformationManager* GetTranslationManager();
                void MarkBlockDirty(int X, int Y, int Z);
        };
    }
}
#endif
