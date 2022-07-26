#pragma once
#include <string>

enum class TextureType
{
	Depth,
	Color,
	Cube
};

class Texture
{
public:
	unsigned int texture;
	int width, height;
	Texture(std::string);
	Texture(TextureType type,int width=0,int heigth=0);
	~Texture();
	void ColorBufferInit(int, int);
	void DepthBufferInit(int, int);
	void CubeMapInit();
private:
	void TextureInit();
};
