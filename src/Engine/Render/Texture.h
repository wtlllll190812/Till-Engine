#pragma once
#include <string>
class Texture
{
public:
	unsigned int texture;
	int width, height;
	Texture(std::string);
	Texture();
	~Texture();
	void ColorBufferInit(int, int);
	void DepthBufferInit(int, int);
private:
	void TextureInit();
};
