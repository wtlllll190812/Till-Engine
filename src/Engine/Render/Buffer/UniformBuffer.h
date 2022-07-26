#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>

/// <summary>
/// UBO缓存
/// </summary>
class UniformBuffer
{
public:
	UniformBuffer();
	~UniformBuffer();
	/// <summary>
	/// 初始化缓存
	/// </summary>
	int BufferInit(int size);
	
	/// <summary>
	/// 获取缓存
	/// </summary>
	inline unsigned int GetBuffer() { return buffer; };
	
	/// <summary>
	/// 设置缓存参数
	/// </summary>
	/// <param name="size">参数大小</param>
	/// <param name="offset">参数的offset位置</param>
	/// <param name="data">参数指针</param>
	void SetData(int size, int offset, const void* data);
private:
	unsigned int buffer;
};

