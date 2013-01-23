#ifndef _ENGINE_CHUNK_H_
#define _ENGINE_CHUNK_H_

#include "Block.hpp"

#define CHUNK_SIZE 16
#define CHUNK_BLOCKS CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE

namespace vox {
    namespace engine {

        class Chunk {
            private:
                int _x, _y, _z;
                Block* _data;
            public:
                //We copy data, dealoc it your self plz.
                Chunk(int X, int Y, int Z, Block* Data);
                Chunk(const Chunk& Other);
                ~Chunk();

                Block GetBlock(int X, int Y, int Z) const;
                Block& GetBlock (int X, int Y, int Z);

                inline int GetX() {return _x;}
                inline int GetY() {return _y;}
                inline int GetZ() {return _z;}
        };
    }
}

#endif
