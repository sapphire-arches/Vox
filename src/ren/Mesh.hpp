#ifndef _REN_MESH_H_
#define _REN_MESH_H_

namespace vox {
    namespace ren {
        struct Vertex {
            float x, y, z;
            float r, g, b;
            float nx, ny, nz;
        };

        class Mesh {
            public:
                Mesh (int* Indicies, int IndLen, Vertex* Verts, int VertLen, int DrawMode);
                ~Mesh();

                void Render();
            private:
                int _iboID;
                int _vboID;
                int _vcount;
                int _drawMode;
        };
    }
}


#endif
