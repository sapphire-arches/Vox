#ifndef _ENGINE_ENTITY_PLAYERENTITY_H_
#define _ENGINE_ENTITY_PLAYERENTITY_H_

#include "engine/entity/Entity.hpp"

namespace vox {
    namespace engine {
        namespace entity {
            class PlayerEntity : public Entity {
                private:
                    float _jpLevel;
                    //No Copypasta
                    PlayerEntity(const PlayerEntity& Other);
                    PlayerEntity& operator= (PlayerEntity& Other);
                public:
                    PlayerEntity(glm::vec3 Pos);

                    virtual void Tick(const vox::engine::World& W);

                    void Jetpack();
                    inline float GetJetpackLevel() {
                        return _jpLevel;
                    }
            };
        }
    }
}

#endif
