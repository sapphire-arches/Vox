#ifndef _ENGINE_ENTITY_PLAYERENTITY_H_
#define _ENGINE_ENTITY_PLAYERENTITY_H_

#include "engine/entity/Entity.hpp"
#define PLAYER_MAX_HEALTH 100
#define PLAYER_MAX_JETPACK 10.f

namespace vox {
    namespace engine {
        namespace entity {
            class PlayerEntity : public Entity {
                private:
                    float _jpLevel;
                    bool _jpNextTick;
                    //No Copypasta
                    PlayerEntity(const PlayerEntity& Other);
                    PlayerEntity& operator= (PlayerEntity& Other);
                public:
                    PlayerEntity(glm::vec3 Pos);

                    virtual void Tick(vox::engine::World& W);

                    void Jetpack();
                    inline float GetJetpackLevel() {
                        return _jpLevel;
                    }
            };
        }
    }
}

#endif
