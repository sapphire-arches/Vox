#ifndef _ENGINE_ENTITY_ENTITY_H_
#define _ENGINE_ENTITY_ENTITY_H_

#include "ren/Mesh.hpp"
#include "ren/TransformationManager.hpp"
#include "engine/phys/PhysicsObject.hpp"
#include <glm/glm.hpp>
#include <boost/shared_ptr.hpp>

namespace vox {
    namespace engine {
        class World;

        namespace entity {
            class Entity : public vox::engine::physics::PhysicsObject {
                private:
                    //Don't want to copy dem entities.
                protected:
                    boost::shared_ptr<vox::ren::Mesh> _mesh;
                    int _health;
                public:
                    Entity(const glm::vec3& Pos, const glm::vec3& Size, int _health);
                    Entity(const glm::vec3& Pos, const glm::vec3& Size, int _health,
                            const vox::engine::physics::PhysicsObject& Parent);
                    
                    Entity(const Entity& Other);
                    Entity& operator= (const Entity& Other);
                    
                    virtual ~Entity() {
                        std::cout << "Freeing entity: " << _id << std::endl;
                    }

                    virtual void Tick(const World& In);
                    virtual void Render(vox::ren::TransformationManager* Manager) const;

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
