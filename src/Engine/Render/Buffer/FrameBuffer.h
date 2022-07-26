#pragma once


enum class BufferType
{
	Color,
	Depth,
	Both
};

class Texture;
/// <summary>
/// 帧缓存
/// </summary>
class FrameBuffer
{
public:
	FrameBuffer(BufferType type);
	~FrameBuffer();
	/// <summary>
	/// 获取缓存ID
	/// </summary>
	unsigned int& GetFBO();
	
	/// <summary>
	/// 重置缓存大小
	/// </summary>
	void Resize(float w, float h);
	int GetWidth();
	int GetHeight();

	/// <summary>
	/// 获取颜色缓存
	/// </summary>
	inline Texture* GetColorBuffer() { return color; };
	
	/// <summary>
	/// 获取深度缓存
	/// </summary>
	inline Texture* GetDepthBuffer() { return depth; };
private:
	Texture* color;
	Texture* depth;
	unsigned int fbo;
};