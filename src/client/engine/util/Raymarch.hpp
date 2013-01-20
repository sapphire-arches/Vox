#ifndef _ENGINE_UTIL_RAYMARCH_H_
#define _ENGINE_UTIL_RAYMARCH_H_

#include "engine/World.hpp"
#include <glm/glm.hpp>

namespace vox {
    namespace engine {
        namespace util {
            //HitPos is output.
            void  Raymarch(vox::engine::World& Wor, glm::vec3 StartPos, glm::vec3 Dir, int* HitPos);
        }
    }
}
                    
#endif
