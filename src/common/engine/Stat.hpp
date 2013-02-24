#ifndef _ENGINE_STAT_H_
#define _ENGINE_STAT_H_

namespace vox {
    namespace engine {
        template <typename T>
        struct Stat {
            T Average;
            T Min;
            T Max;
            T Total;
            T Current;
            long long Count;
        };
    }
}

#endif
