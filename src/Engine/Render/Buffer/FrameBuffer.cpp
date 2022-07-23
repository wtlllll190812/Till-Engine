#include "FrameBuffer.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include "Texture.h"

FrameBuffer::FrameBuffer(BufferType type)
{
	color = nullptr;
	depth = nullptr;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	switch (type)
	{
	case BufferType::Color:
		color = new Texture();
		color->ColorBufferInit(800, 600);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color->texture, 0);
		break;
	case BufferType::Depth:
		depth = new Texture();
		depth->DepthBufferInit(800, 600);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depth->texture, 0);
		break;
	case BufferType::Both:
		color = new Texture();
		color->ColorBufferInit(800, 600);
		depth = new Texture();
		depth->DepthBufferInit(800, 600);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color->texture, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depth->texture, 0);
		break;
	default:
		break;
	}
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
	color->ColorBufferInit(w, h);
	depth->DepthBufferInit(w, h);
}

int FrameBuffer::GetWidth()
{
	return color->width;
}

int FrameBuffer::GetHeight()
{
	return color->height;
}
