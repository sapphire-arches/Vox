#ifndef _ENGINE_CAMERA_H_
#define _ENGINE_CAMERA_H_

#include "engine/entity/PlayerEntity.hpp"

namespace vox {
    namespace engine {
        namespace entity {
            class Camera {
                private:
                    PlayerEntity& _follow;
                    float _yaw, _pitch;

                    Camera(const Camera& Other);
                    Camera& operator= (const Camera& Other);
                public:
                    Camera(const glm::vec3 Pos, PlayerEntity& ToFollow);

                    void Tick(const vox::engine::World& In);
                    void OnMouseMove(int XDelta, int YDelta);
 
                    PlayerEntity& GetEnt() const;
                    glm::vec3 GetDirection() const;
                    glm::vec3 GetPosition() const;
            };
        }
    }
}

#endif
