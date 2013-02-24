#include "Entity.hpp"
#include <GL/glew.h>
#include <iostream>

using namespace vox::engine;
using namespace vox::engine::entity;

using glm::vec3;

Entity::Entity(const vec3& Pos, const vec3& Size, int Health) : 
    PhysicsObject(Pos, Size, Size.x * Size.y * Size.z) {
    _health = Health;
}

Entity::Entity(const vec3& Pos, const vec3& Size, int Health,
        const PhysicsObject& Parent) 
    : PhysicsObject(Pos, Size, Size.x * Size.y * Size.z, Parent) {
    _health = Health;
}


Entity::Entity(const Entity& Other) : PhysicsObject(Other) {
    _health = Other._health;
    _aabb = Other._aabb;
}

Entity& Entity::operator= (const Entity& Other) {
    if (&Other != this) {
        return *this;
    }
    _aabb = Other._aabb;
    _health = Other._health;

    return *this;
}

void Entity::Tick(World& In) {
    DoPhysics(In);
    //Nothing else to do here...
}
