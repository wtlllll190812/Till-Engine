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
		color = new Texture(TextureType::Color, 1080, 720);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color->texture, 0);
		break;
	case BufferType::Depth:
		depth = new Texture(TextureType::Depth, 1080, 720);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth->texture, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		break;
	case BufferType::Both:
		color = new Texture(TextureType::Color, 1080, 720);
		depth = new Texture(TextureType::Depth, 1080, 720);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color->texture, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth->texture, 0);
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
	if(color) color->ColorBufferInit(w, h);
	if(depth) depth->DepthBufferInit(w, h);
}

int FrameBuffer::GetWidth()
{
	if(color)
		return color->width;
	return depth->width;
}

int FrameBuffer::GetHeight()
{
	if (color)
		return color->height;
	return depth->height;
}
