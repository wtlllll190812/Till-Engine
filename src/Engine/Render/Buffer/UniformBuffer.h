#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>

class UniformBuffer
{
public:
	UniformBuffer();
	~UniformBuffer();
	int BufferInit(int size);
	inline unsigned int GetBuffer() { return buffer; };
	
	void SetData(int size, int offset, const void* data);
private:
	unsigned int buffer;
};

