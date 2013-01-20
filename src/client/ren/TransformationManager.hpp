#ifndef _REN_TRANSFORMATIONMANAGER_H_
#define _REN_TRANSFORMATIONMANAGER_H_

#include <stack>
#include <glm/glm.hpp>

namespace vox {
    namespace ren {
        typedef std::stack<glm::mat4> MatrixStack;

        class TransformationManager {
            private:
                MatrixStack _mstack;
                glm::mat4 _modelview;
                glm::mat4 _projection;
                int _mviewLoc;
                int _pLoc;
            public:
                TransformationManager(float FOV, float Aspect);
                TransformationManager(const TransformationManager& Other);
                ~TransformationManager();

                void PushMatrix();
                void PopMatrix();    

                void Translate(float X, float Y, float Z);
                void Translate(glm::vec3 Amount);
                void Rotate(float Pitch, float Yaw, float Roll);
                void Rotate(glm::vec3 Axis, float angle);

                void BuildProjectionMatrix(float FOV, float Aspect);

                void SetLocations(int MViewLoc, int PLoc);
                void ToGPU();

                glm::vec3 Unproject(glm::vec3 V);

                TransformationManager& operator= (const TransformationManager& Other);
        };
    }
};

#endif
