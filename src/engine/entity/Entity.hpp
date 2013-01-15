#ifndef _ENGINE_ENTITY_ENTITY_H_
#define _ENGINE_ENTITY_ENTITY_H_

#include "ren/Mesh.hpp"
#include "ren/TransformationManager.hpp"
#include "engine/phys/PhysicsObject.hpp"
#include <glm/glm.hpp>

namespace vox {
    namespace engine {
        class World;

        namespace entity {
            class Entity : public vox::engine::physics::PhysicsObject {
                private:
                    vox::ren::Mesh* _mesh;

                    //Don't want to copy dem entities.
                    Entity(const Entity& Other);
                    Entity& operator= (const Entity& Other);
                public:
                    Entity(const glm::vec3& Pos, const glm::vec3& Size);
                    ~Entity();

                    virtual void Tick(const World& In);
                    virtual void Render(vox::ren::TransformationManager* Manager) const;

                    float _yaw;
            };
        }
    }
}

#endif
