#ifndef _ENGINE_ENTITY_ROCKET_H_
#define _ENGINE_ENTITY_ROCKET_H_

#include "Entity.hpp"

namespace vox {
    namespace engine {
        namespace entity {
            class Rocket : public Entity {
                private:
                    glm::vec3 _dir;
                    bool _detonate;
                public:
                    Rocket(const glm::vec3 Pos, const glm::vec3 Dir, const PhysicsObject& Parent);
                    ~Rocket() {
                        std::cout << "ROCKETBLARG" << std::endl;
                    }

                    virtual void Tick(vox::engine::World& W);
                    virtual void OnWorldHit(int X, int Y, int Z);
            };
        }
    }
}

#endif
