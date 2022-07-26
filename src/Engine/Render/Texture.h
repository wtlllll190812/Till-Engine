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

	/// <summary>
	/// 用于颜色缓存的初始化
	/// </summary>
	void ColorBufferInit(int, int);
	
	/// <summary>
	/// 用于深度缓冲的初始化
	/// </summary>
	void DepthBufferInit(int, int);
	
	/// <summary>
	/// 用于立方体贴图的初始化
	/// </summary>
	void CubeMapInit();
private:
	void TextureInit();
};
