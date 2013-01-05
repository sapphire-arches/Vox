#ifndef _REN_GL_SHADER_H_
#define _REN_GL_SHADER_H_

#include <map>
#include <string>

namespace vox {
    namespace ren {
        namespace gl {
            class Shader {
                public:
                    Shader(std::string Source, int ShaderType);
                    ~Shader();
                private:
                    int _shaderID;
                    friend class ShaderProgram;
            };

            class VertexShader : public Shader {
                public:
                    VertexShader(std::string Source);
                    ~VertexShader();
                private:
                    //Nothing needed
            };

            class FragmentShader : public Shader{
                public:
                    FragmentShader(std::string Source);
                    ~FragmentShader();
                private:
                    //Nothing do see here
            };

            typedef std::map<std::string, int> UniformMap;

            class ShaderProgram {
                public:
                    ShaderProgram();
                    ~ShaderProgram();

                    void AttachVertexShader(VertexShader& VertShader);
                    void AttachFragmentShader(FragmentShader& FragShader);
                    void Use();

                    void PrintInfoLog();

                    ShaderProgram& operator= (const ShaderProgram& rhs);
                private:
                    int _programID;
                    bool _link;
                    UniformMap _uniforms;

                    void EnsureLink();
            };


        }
    }
}
#endif
