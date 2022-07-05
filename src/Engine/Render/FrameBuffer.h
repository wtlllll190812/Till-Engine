#pragma once

class Texture;
class FrameBuffer
{
public:
	FrameBuffer();
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
