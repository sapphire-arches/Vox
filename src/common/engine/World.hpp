#ifndef _ENGINE_WORLD_H_INCLUDED
#define _ENGINE_WORLD_H_INCLUDED

#include "ChunkCache.hpp"
#include <list>
#include "engine/entity/PlayerEntity.hpp"
#include "engine/entity/Entity.hpp"
#include "engine/entity/Camera.hpp"
#include <boost/signals2.hpp>

namespace vox {
    namespace engine {
        
        typedef std::list<vox::engine::entity::Entity*> EntityList;
        typedef EntityList::iterator EntityListIterator;

        class World {
            private:
                ChunkCache _cache;
                EntityList _ents;
                vox::engine::entity::PlayerEntity& _player;
                vox::engine::entity::Camera _cam;

                //No copypasta
                World(const World& Other);
                World& operator= (const World& Other);
            public:
                World();
                ~World();
                
                int GetBlock(int X, int Y, int Z);
                void SetBlock(int X, int Y, int Z, unsigned char Val);
                
                //Arguments are X, Y, Z, value.
                boost::signals2::signal<void (int, int, int, unsigned char To)> OnBlockSet;

                void AddEntity(vox::engine::entity::Entity* Ent);
                boost::signals2::signal<void (vox::engine::entity::Entity*)> OnAddEntity;
                boost::signals2::signal<void (vox::engine::entity::Entity*)> OnRemoveEntity;
                void Tick();

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
