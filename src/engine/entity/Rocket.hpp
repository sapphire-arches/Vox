#ifndef _ENGINE_ENTITY_ROCKET_H_
#define _ENGINE_ENTITY_ROCKET_H_

#include "Entity.hpp"

namespace vox {
    namespace engine {
        namespace entity {
            class Rocket : public Entity {
                private:
                    glm::vec3 _dir;
                public:
                    Rocket(glm::vec3 Pos, glm::vec3 Dir);
                    ~Rocket();

                    virtual void Tick(const vox::engine::World& W);
            };
        }
    }
}

#endif
