#ifndef _ENGINE_UTIL_SPATIALHASHTABLE_H_
#define _ENGINE_UTIL_SPATIALHASHTABLE_H_

namespace vox {
    namespace engine {
        namespace util {
            template <class T, int Size>
                class SpatialHashtable {
                    private:
                        T *_data;
                    public:
                        SpatialHashtable();
                        ~SpatialHashtable();

                        T* Get(int X, int Y, int Z);
                        void Set(int X, int Y, int Z, T* Val);
                };
        }
    }
}

#endif
