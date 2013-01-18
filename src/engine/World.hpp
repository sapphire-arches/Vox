#ifndef _ENGINE_WORLD_H_INCLUDED
#define _ENGINE_WORLD_H_INCLUDED

#include "ChunkCache.hpp"
#include <list>
#include "engine/entity/PlayerEntity.hpp"
#include "engine/entity/Entity.hpp"
#include "engine/entity/Camera.hpp"
#include "state/GameState.hpp"

namespace vox {
    namespace ren {
        class WorldRenderer;
    }

    namespace engine {
        
        typedef std::list<vox::engine::entity::Entity*> EntityList;
        typedef EntityList::iterator EntityListIterator;

        class World {
            private:
                ChunkCache _cache;
                EntityList _ents;
                vox::ren::WorldRenderer* _ren;
                vox::engine::entity::PlayerEntity& _player;
                vox::engine::entity::Camera _cam;

                //No copypasta
                World(const World& Other);
                World& operator= (const World& Other);
            public:
                World();
                ~World();
                
                unsigned char& operator() (int X, int Y, int Z);
                unsigned char operator() (int X, int Y, int Z) const;

                void AddEntity(vox::engine::entity::Entity* Ent);
                void Tick();
                void Render(vox::state::Gamestate& State);

                glm::vec3 Unproject(glm::vec3 V);

                inline vox::ren::WorldRenderer* GetRenderer() {
                    return _ren;
                }

                inline vox::engine::entity::PlayerEntity& GetPlayer() {
                    return _player;
                }

                inline vox::engine::entity::Camera& GetCamera() {
                    return _cam;
                }
        };
    }
}

#endif
