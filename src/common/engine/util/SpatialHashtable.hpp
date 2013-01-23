#ifndef _ENGINE_UTIL_SPATIALHASHTABLE_H_
#define _ENGINE_UTIL_SPATIALHASHTABLE_H_

#include <cstring>

namespace vox {
    namespace engine {
        namespace util {
            template <class T, int Size>
                class SpatialHashtable {
                    private:
                        T *_data;
                    public:
                        SpatialHashtable() {
                            _data = new T[Size * Size * Size];
                            memset(_data, 0, Size * Size * Size * sizeof(T*));
                        }

                        ~SpatialHashtable() {
                            for (int i = 0; i < Size * Size * Size; ++i) {
                                if (_data[i] != NULL) {
                                    delete _data[i];
                                }
                            }
                            delete[] _data;
                        }

                        T Get(int X, int Y, int Z) {
                            int x = X % Size;
                            int y = Y % Size;
                            int z = Z % Size;
                            if (x < 0) {
                                x += Size;
                            }
                            if (y < 0) {
                                y += Size;
                            }
                            if (z < 0) {
                                z += Size;
                            }
                            return _data[x + y * Size + z * Size * Size];
                        }

                        void Set(int X, int Y, int Z, T Val) {
                            int x = X % Size;
                            int y = Y % Size;
                            int z = Z % Size;
                            if (x < 0) {
                                x += Size;
                            }
                            if (y < 0) {
                                y += Size;
                            }
                            if (z < 0) {
                                z += Size;
                            }
                            _data[x + y * Size + z * Size * Size] = Val;
                        }
                };
        }
    }
}

#endif
