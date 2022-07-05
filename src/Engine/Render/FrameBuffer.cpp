#include "FrameBuffer.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include "Texture.h"
#include "Debug.h"

FrameBuffer::FrameBuffer()
{
    texture = new Texture();
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->texture, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &fbo);
    delete texture;
}

unsigned int& FrameBuffer::GetFBO()
{
    return fbo;
}

void FrameBuffer::Resize(float w, float h)
{
    texture->Resize(w,h);
}
