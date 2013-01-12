#ifndef _ENGINE_ENTITY_ENTITY_H_
#define _ENGINE_ENTITY_ENTITY_H_

#include "ren/Mesh.hpp"
#include <glm/glm.hpp>

namespace vox {
    namespace engine {
        class World;

        namespace entity {
            class Entity {
                private:
                    glm::vec3 _pos;
                    glm::vec3 _vel;
                    glm::vec3 _acc;
                    vox::ren::Mesh* _mesh;

                    //Don't want to copy dem entities.
                    Entity(const Entity& Other);
                    Entity& operator= (const Entity& Other);
                public:
                    Entity(const glm::vec3& Pos);
                    ~Entity();

                    virtual void Tick(const World& In);
                    void ApplyForce(const glm::vec3& Force);
                    virtual void Render();
            };
        }
    }
}

#endif
