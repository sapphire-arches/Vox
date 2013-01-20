#ifndef CLIENT_REN_ENTITYRENDERER_H_
#define CLIENT_REN_ENTITYRENDERER_H_

#include "engine/entity/Entity.hpp"
#include "TransformationManager.hpp"
#include "Mesh.hpp"
#include <boost/smart_ptr.hpp>

namespace vox {
    namespace ren {
        class EntityRenderer {
            private:
                vox::engine::entity::Entity& _ent;
                boost::shared_ptr<vox::ren::Mesh> _mesh;
            public:
                EntityRenderer(vox::engine::entity::Entity& ent);
                ~EntityRenderer();

                void Render(TransformationManager* Manager) const;
        };
    }
}

#endif
