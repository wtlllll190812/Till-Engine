#pragma once

class Texture;
class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();
	unsigned int &GetFBO();
	void Resize(float w, float h);
private:
	Texture* texture;
	unsigned int fbo;
};

