#ifndef _ENGINE_UTIL_PERLIN_H_
#define _ENEINE_UTIL_PERLIN_H_

namespace vox {
    namespace engine {
        namespace util {
            class Perlin3D {
                private:
                    float* _data;
                public:
                    Perlin3D(int Seed);
                    Perlin3D(const Perlin3D& Other);
                    ~Perlin3D();

                    float Get(float X, float Y, float Z);

                    Perlin3D& operator= (const Perlin3D& Other);
            };
        }
    }
}

#endif
