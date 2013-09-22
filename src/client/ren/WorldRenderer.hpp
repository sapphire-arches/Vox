#ifndef _REN_WORLD_RENDERER_H_INCLUDED_
#define _REN_WORLD_RENDERER_H_INCLUDED_

#include <stack>
#include <set>
#include <boost/static_assert.hpp>
#include <glm/glm.hpp>

#include "Mesh.hpp"
#include "RenderChunk.hpp"
#include "TransformationManager.hpp"
#include "EntityRenderer.hpp"

namespace vox {
    namespace engine {
        class World;
    }

    namespace ren {
        namespace gl {
            class ShaderProgram;
        }

        class WorldRenderer;

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
                std::list<EntityRenderer*> _ents;
                friend struct ToBuildChunk;

                void DoRenderChunk(int X, int Y, int Z);
            public:
                float _yaw, _pitch, _roll;
                WorldRenderer(vox::engine::World& For);
                ~WorldRenderer();

                void Render();

                void SetCameraPosition(float X, float Y, float Z);
                void SetCameraPosition(glm::vec3 Vec);
                void SetCameraDirection(float Yaw, float Pitch, float Roll);
                vox::ren::TransformationManager* GetTranslationManager();
                void MarkBlockDirty(int X, int Y, int Z);
                void AddEntityRenderer(EntityRenderer* Ent);
                void RemoveEntityRenderer(EntityRenderer* Ent);
                void RemoveRendererForEntity(vox::engine::entity::Entity* Ent);
        };
    }
}
#endif
