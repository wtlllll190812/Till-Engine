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
	void ColorInit(int, int);
	void DepthInit(int, int);
private:
	void TextureInit();
};
