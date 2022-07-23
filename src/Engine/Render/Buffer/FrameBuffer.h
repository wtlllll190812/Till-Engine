#pragma once


enum class BufferType
{
	Color,
	Depth,
	Both
};

class Texture;
class FrameBuffer
{
public:
	FrameBuffer(BufferType type);
	~FrameBuffer();
	unsigned int& GetFBO();
	void Resize(float w, float h);
	int GetWidth();
	int GetHeight();
private:
	Texture* color;
	Texture* depth;
	unsigned int fbo;
};