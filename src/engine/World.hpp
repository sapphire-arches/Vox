#ifndef _ENGINE_WORLD_H_INCLUDED
#define _ENGINE_WORLD_H_INCLUDED

namespace vox {
    namespace engine {
        class World {
            public:
                World();
                ~World();

                int& operator() (int x, int y, int z);
                int operator() (int x, int y, int z) const;
            private:
                //TODO: implement infinte stuff
                int* _data;
        };
    }
}

#endif
