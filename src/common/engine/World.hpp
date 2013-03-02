#ifndef _ENGINE_WORLD_H_INCLUDED
#define _ENGINE_WORLD_H_INCLUDED

#include "ChunkCache.hpp"
#include "ChunkProvider.hpp"
#include <list>
#include "engine/entity/PlayerEntity.hpp"
#include "engine/entity/Entity.hpp"
#include "engine/entity/Camera.hpp"
#include <boost/signals.hpp>

namespace vox {
    namespace engine {
        
        typedef std::list<vox::engine::entity::Entity*> EntityList;
        typedef EntityList::iterator EntityListIterator;

        class World {
            private:
                ChunkCache _cache;
                EntityList _ents;
                //No copypasta
                World(const World& Other);
                World& operator= (const World& Other);
            public:
                World();
                ~World();
                
                Block GetBlock(int X, int Y, int Z);
                void SetBlock(int X, int Y, int Z, Block Val);
                
                //Arguments are X, Y, Z, value.
                boost::signal<void (int, int, int, unsigned char To)> OnBlockSet;

                void AddEntity(vox::engine::entity::Entity* Ent);
                boost::signal<void (vox::engine::entity::Entity*)> OnAddEntity;
                boost::signal<void (vox::engine::entity::Entity*)> OnRemoveEntity;
                void Tick(int& DT);

                void SetChunkProvider(ChunkProvider* Provider);
        };
    }
}

#endif
