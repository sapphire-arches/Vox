#ifndef _ENGINE_CAMERA_H_
#define _ENGINE_CAMERA_H_

#include "engine/entity/Entity.hpp"
#include "engine/phys/PhysicsObject.hpp"

namespace vox {
    namespace engine {
        namespace entity {
            class Camera : public vox::engine::physics::PhysicsObject {
                private:
                    Entity& _follow;

                    Camera(const Camera& Other);
                    Camera& operator= (const Camera& Other);
                public:
                    Camera(const glm::vec3 Pos, Entity& ToFollow);

                    void Tick(const vox::engine::World& In);
                    Entity& GetEnt() const;
                    glm::vec3 GetDirection() const;
            };
        }
    }
}

#endif
