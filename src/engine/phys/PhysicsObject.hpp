#ifndef _ENGINE_PHYS_PHYSICSOBJECT_H_
#define _ENGINE_PHYS_PHYSICSOBJECT_H_

#include "Types.hpp"
#include <glm/glm.hpp>

namespace vox {
    namespace engine {
        class World;

        namespace physics {
            class PhysicsObject {
                protected:
                    AABB _aabb;
                    glm::vec3 _lastPos;
                    glm::vec3 _vel;
                    glm::vec3 _acc;
                    bool _onground;
                    float _mass;
                public:
                    PhysicsObject (const glm::vec3& Pos, glm::vec3 Size, float Mass);
                    
                    void DoPhysics(const World& In);
                    void ApplyForce(const glm::vec3& Force);
                    void ResolveCollision(PhysicsObject& Other);
                    
                    float GetMass() const;
                    bool IsOnGround() const;

                    glm::vec3 GetPosition() const;

                    inline bool Intersects(PhysicsObject Other) {
                        return _aabb.Intersects(Other._aabb);
                    }
            };
        }
    }
}

#endif
