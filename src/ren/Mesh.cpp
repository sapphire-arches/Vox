#include "Mesh.hpp"
#include <GL/glew.h>
#include <iostream>

using namespace vox::ren;

/************************************************\
**************************************************
**                 MESH MEMBERS                 **
**************************************************
\************************************************/
Mesh::Mesh (int *Indicies, int IndLen, Vertex* Verts, int VertLen, int DrawMode) {
    _vcount = IndLen;
    _drawMode = DrawMode;
    std::cout << "Mesh created with " << _vcount << " verts." << std::endl;
    GLuint temp[2];
    glGenBuffersARB(2, temp);
    _iboID = temp[0];
    _vboID = temp[1];

    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, _iboID);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, _vboID);

    glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, IndLen * sizeof(int),
            Indicies, GL_STATIC_DRAW_ARB);
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, VertLen * sizeof(Vertex),
            Verts, GL_STATIC_DRAW_ARB);

    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
}

Mesh::~Mesh() {
    //TODO: Figure out how to do memory managment for the buffers
}

void Mesh::Render() {
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, _iboID);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, _vboID);

    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), 0);
    glColorPointer (3, GL_FLOAT, sizeof(Vertex), (GLvoid*) (3 * sizeof(float)));
    glNormalPointer(   GL_FLOAT, sizeof(Vertex), (GLvoid*) (6 * sizeof(float)));

    glDrawElements(_drawMode, _vcount, GL_UNSIGNED_INT, 0);

    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
}

/************************************************\
**************************************************
**               VERTEX MEMBERS                 **
**************************************************
\************************************************/

Vertex::Vertex(float X, float Y, float Z) {
    x = X;
    y = Y;
    z = Z;
}

Vertex::Vertex() {
}
