#ifndef _ENGINE_CAMERA_H_
#define _ENGINE_CAMERA_H_

#include "engine/entity/PlayerEntity.hpp"
#include "engine/phys/PhysicsObject.hpp"

namespace vox {
    namespace engine {
        namespace entity {
            class Camera : public vox::engine::physics::PhysicsObject {
                private:
                    PlayerEntity& _follow;

                    Camera(const Camera& Other);
                    Camera& operator= (const Camera& Other);
                public:
                    Camera(const glm::vec3 Pos, PlayerEntity& ToFollow);

                    void Tick(const vox::engine::World& In);
 
                    PlayerEntity& GetEnt() const;
                    glm::vec3 GetDirection() const;
            };
        }
    }
}

#endif
