#include "RenderManager.hpp"

#include "GraphicsDefs.hpp"
#include "ren/gl/Util.hpp"

#include <iostream>
#include <cstdlib>

using namespace vox::ren;
using namespace vox::ren::gl;

RenderManager::RenderManager() {
    glGenFramebuffers(1, &this->RenderBufferName);
    PrintGLError("Gen framebuffer");
    glBindFramebuffer(GL_FRAMEBUFFER, this->RenderBufferName);

    glGenTextures(1, &this->RenderTexture);
    glBindTexture(GL_TEXTURE_2D, this->RenderTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    PrintGLError("Generate and set up texture");

    glGenRenderbuffers(1, &this->DepthRenderBuffer);
    PrintGLError("Generate render buffer");
    glBindRenderbuffer(GL_RENDERBUFFER, this->DepthRenderBuffer);
    PrintGLError("Bind depth buffer");
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WIDTH, HEIGHT);
    PrintGLError("Set depth buffer storage");
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->DepthRenderBuffer);
    PrintGLError("Bind depth buffer to frame buffer");

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->RenderTexture, 0);
    PrintGLError("attach color buffer");

    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);
    std::cout << "Attached draw buffers" << std::endl;

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Failed to set up frame buffer" << std::endl;
        exit(-1);
    }
    std::cout << "Frame buffer configured" << std::endl;
    PrintGLError("Framebuffer Config");
}

RenderManager::~RenderManager() {
}

void RenderManager::EnterGameWorldRender() {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, RenderBufferName);
    glViewport(0, 0, WIDTH, HEIGHT);
}

void RenderManager::LeaveGameWorldRender() {
    glDisable(GL_DEPTH_TEST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, this->RenderBufferName);
    glBlitFramebuffer(0, 0, WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    PrintGLError("Gameworld Render");
}

void RenderManager::EnterHUDRender() {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void RenderManager::LeaveHUDRender() {
    glDisable(GL_DEPTH_TEST);
}

void RenderManager::OnResize(int w, int h) {
}
