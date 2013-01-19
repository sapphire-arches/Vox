#ifndef _MATHUTIL_H_
#define _MATHUTIL_H_

namespace vox {
    inline int Floor(float F) {
        if (F < 0)
            return (int) F - 1;
        return (int) F;
    }
}

#endif
