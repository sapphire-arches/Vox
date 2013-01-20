#include "Util.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

void vox::ren::gl::PrintGLError(const char* Place) {
    int i = glGetError();
    if (i != GL_NO_ERROR) {
        std::cout << "OpenGL Error at " << Place << " is ";
        switch(i) {
            case GL_INVALID_ENUM:                  std::cout << "GL_INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 std::cout << "GL_INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             std::cout << "GL_INVALID_OPERATION"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
            case GL_OUT_OF_MEMORY:                 std::cout << "GL_OUT_OF_MEMORY"; break;
            case GL_STACK_UNDERFLOW:               std::cout << "GL_STACK_UNDERFLOW"; break;
            case GL_STACK_OVERFLOW:                std::cout << "GL_STACK_OVERFLOW"; break;
        }
        std::cout << std::endl;
    }
}
