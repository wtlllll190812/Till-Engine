#include "Texture.h"
#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <SOIL2/SOIL2.h>

Texture::Texture(std::string path)
{
	TextureInit();
	unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image); //生成纹理(纹理目标,指定mipmap级别,存储格式,宽度,高度,0,原图格式,数据类型)
	glGenerateMipmap(GL_TEXTURE_2D);														   //生成mipmap
	SOIL_free_image_data(image);															   //释放内存
	glBindTexture(GL_TEXTURE_2D, 0);														   //解绑
}

Texture::Texture()
{
	TextureInit();
	glBindTexture(GL_TEXTURE_2D, 0);														   //解绑
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}

void Texture::ColorInit(int w, int h)
{
	if (w != width || h != height)
	{
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);
		width = w;
		height = h;
	}
}

void Texture::DepthInit(int w, int h)
{
	if (w != width || h != height)
	{
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, w, h, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);
		width = w;
		height = h;
	}
}

void Texture::TextureInit()
{
	glGenTextures(1, &texture);									  //设定纹理数量,及存储数组
	glBindTexture(GL_TEXTURE_2D, texture);						  //绑定纹理

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}