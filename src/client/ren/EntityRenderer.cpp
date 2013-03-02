#include "EntityRenderer.hpp"
#include <GL/glew.h>

using namespace vox::engine::entity;
using namespace vox::ren;

EntityRenderer::EntityRenderer(Entity& Ent) : _ent(Ent){
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

    glm::vec3 size = Ent.GetSize();

    for (int i = 0; i < 8; ++i) {
        verts[i].r = 1.f;
        verts[i].g = 0.5f;
        verts[i].b = 0.5f;
        verts[i].x *= size.x; verts[i].y *= size.y; verts[i].z *= size.z;
    }

    ind[ 0] = 0; ind[ 1] = 1; ind[ 2] = 3; ind[ 3] = 2;
    ind[ 4] = 4; ind[ 5] = 6; ind[ 6] = 7; ind[ 7] = 5;
    ind[ 8] = 0; ind[ 9] = 2; ind[10] = 6; ind[11] = 4;
    ind[12] = 3; ind[13] = 1; ind[14] = 5; ind[15] = 7;
    ind[16] = 2; ind[17] = 3; ind[18] = 7; ind[19] = 6;
    ind[20] = 0; ind[21] = 4; ind[22] = 5; ind[23] = 1;

    _mesh = boost::shared_ptr<Mesh>(new Mesh(ind, 24, verts, 24, GL_QUADS));
}

void EntityRenderer::Render(TransformationManager* Manager) const {
    glm::vec3 ePos = _ent.GetPosition();
    Manager->Translate(ePos.x, ePos.y, ePos.z);
    Manager->Rotate(0, 0, 0);
    Manager->ToGPU();
    _mesh->Render();
}

bool EntityRenderer::IsRendererFor(Entity* Ent) const {
    return Ent == &_ent;
}
