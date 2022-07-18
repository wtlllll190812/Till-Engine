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
	
	template<class T>
	void Setdata(T data,int offset) 
	{
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(data), offset, data);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	};
private:
	unsigned int buffer;
};

