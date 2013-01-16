#ifndef _REN_HUD_H_
#define _REN_HUD_H_

#include "engine/entity/PlayerEntity.hpp"

namespace vox {
    namespace ren {
        namespace hud {
            class HUD {
                private:
                    vox::engine::entity::PlayerEntity& _moniter;

                    //Just like every other OpenGL interacting class, no copypasta.
                    HUD(const HUD& Other);
                    HUD& operator= (const HUD& Other);
                public:
                    HUD(vox::engine::entity::PlayerEntity& Moniter);
                    ~HUD();

                    void SetJetpackFill(float Percent);
                    void Render();
            };
        }
    }
}

#endif
