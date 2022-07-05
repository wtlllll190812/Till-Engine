#include "FrameBuffer.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include "Texture.h"

FrameBuffer::FrameBuffer()
{
	color = new Texture();
	color->ColorInit(800, 600);
	depth = new Texture();
	depth->DepthInit(800, 600);
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color->texture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depth->texture, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &fbo);
	delete color;
	delete depth;
}

unsigned int& FrameBuffer::GetFBO()
{
	return fbo;
}

void FrameBuffer::Resize(float w, float h)
{
	color->ColorInit(w, h);
	depth->DepthInit(w, h);
}

int FrameBuffer::GetWidth()
{
	return color->width;
}

int FrameBuffer::GetHeight()
{
	return color->height;
}
