#include "Entity.hpp"
#include "ren/TransformationManager.hpp"
#include <GL/glew.h>
#include <iostream>

using namespace vox::engine;
using namespace vox::engine::entity;
using namespace vox::ren;

using glm::vec3;

Entity::Entity(const vec3& Pos, const vec3& Size) : PhysicsObject(Pos, Size, Size.x * Size.y * Size.z) {
    Vertex verts[8];
    int ind[24];

    verts[0].x = 0; verts[0].y = 0; verts[0].z = 0;
    verts[1].x = 0; verts[1].y = 0; verts[1].z = 1;
    verts[2].x = 0; verts[2].y = 1; verts[2].z = 0;
    verts[3].x = 0; verts[3].y = 1; verts[3].z = 1;
    verts[4].x = 1; verts[4].y = 0; verts[4].z = 0;
    verts[5].x = 1; verts[5].y = 0; verts[5].z = 1;
    verts[6].x = 1; verts[6].y = 1; verts[6].z = 0;
    verts[7].x = 1; verts[7].y = 1; verts[7].z = 1;

    for (int i = 0; i < 8; ++i) {
        verts[i].r = 1.f;
        verts[i].g = 0.5f;
        verts[i].b = 0.5f;
        verts[i].x *= 1.f; verts[i].y *= 2.f; verts[i].z *= 1.f;
    }

    ind[ 0] = 0; ind[ 1] = 1; ind[ 2] = 3; ind[ 3] = 2;
    ind[ 4] = 4; ind[ 5] = 6; ind[ 6] = 7; ind[ 7] = 5;
    ind[ 8] = 0; ind[ 9] = 2; ind[10] = 6; ind[11] = 4;
    ind[12] = 3; ind[13] = 1; ind[14] = 5; ind[15] = 7;
    ind[16] = 2; ind[17] = 3; ind[18] = 7; ind[19] = 6;
    ind[20] = 0; ind[21] = 4; ind[22] = 5; ind[23] = 1;

    _mesh = new Mesh(ind, 24, verts, 24, GL_QUADS);
}

Entity::~Entity() {
    //Nothing to do here.
}

void Entity::Tick(const World& In) {
    DoPhysics(In);
    //Nothing else to do here...
}

void Entity::Render(TransformationManager* Manager) const {
    Manager->Translate(_aabb.X, _aabb.Y, _aabb.Z);
    Manager->Rotate(0, _yaw, 0);
    Manager->ToGPU();
    _mesh->Render();
}
