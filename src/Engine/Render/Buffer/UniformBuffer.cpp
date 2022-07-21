#include "UniformBuffer.h"
#include "Debug.h"



UniformBuffer::UniformBuffer()
{
	glGenBuffers(1, &buffer);
}

UniformBuffer::~UniformBuffer()
{
	
}

int UniformBuffer::BufferInit(int size)
{
	static int bufferIndex = 0;
	glBindBuffer(GL_UNIFORM_BUFFER, buffer);
	glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, bufferIndex, buffer, 0, size);
	return bufferIndex++;
}
void UniformBuffer::SetData(int size,int offset,const void* data)
{
	glBindBuffer(GL_UNIFORM_BUFFER, buffer);
	glBufferSubData(GL_UNIFORM_BUFFER,offset,size, data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
