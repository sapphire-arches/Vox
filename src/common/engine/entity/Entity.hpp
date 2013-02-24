#ifndef _ENGINE_ENTITY_ENTITY_H_
#define _ENGINE_ENTITY_ENTITY_H_

#include "engine/phys/PhysicsObject.hpp"
#include <glm/glm.hpp>
#include <boost/shared_ptr.hpp>

namespace vox {
    namespace engine {
        class World;

        namespace entity {
            class Entity : public vox::engine::physics::PhysicsObject {
                protected:
                    int _health;
                public:
                    Entity(const glm::vec3& Pos, const glm::vec3& Size, int _health);
                    Entity(const glm::vec3& Pos, const glm::vec3& Size, int _health,
                            const vox::engine::physics::PhysicsObject& Parent);
                    
                    Entity(const Entity& Other);
                    Entity& operator= (const Entity& Other);
                    
                    virtual ~Entity() {
                    }

                    virtual void Tick(World& In);

                    void Hurt(int Damage);
                    
                    int GetHealth() {
                        return _health;
                    }

                    float Yaw;
            };
        }
    }
}

#endif
