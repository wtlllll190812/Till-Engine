#include "Texture.h"
#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <SOIL2/SOIL2.h>
#include <vector>
#include "Debug.h"
//临时
#include "TLCore.h"

Texture::Texture(std::string path)
{
	TextureInit();
	unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image); //生成纹理(纹理目标,指定mipmap级别,存储格式,宽度,高度,0,原图格式,数据类型)
	glGenerateMipmap(GL_TEXTURE_2D);														   //生成mipmap
	SOIL_free_image_data(image);															   //释放内存
	glBindTexture(GL_TEXTURE_2D, 0);														   //解绑
}

Texture::Texture(TextureType type,int w,int h)
{
	glGenTextures(1, &texture);
	switch (type)
	{
	case TextureType::Depth:
		DepthBufferInit(w, h);
		break;
	case TextureType::Color:
		ColorBufferInit(w, h);
		break;
	case TextureType::Cube:
		CubeMapInit();
		break;
	default:
		break;
	}
	width = w;
	height = h;
	//TextureInit();
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}

void Texture::ColorBufferInit(int w, int h)
{
	if (w != width || h != height)
	{
		glBindTexture(GL_TEXTURE_2D, texture);						  //绑定纹理
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		width = w;
		height = h;
	}
}

void Texture::DepthBufferInit(int w, int h)
{
	if (w != width || h != height)
	{
		glBindTexture(GL_TEXTURE_2D, texture);						  //绑定纹理
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, w, h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		glBindTexture(GL_TEXTURE_2D, 0);
		width = w;
		height = h;
	}
}

void Texture::CubeMapInit()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	std::vector<const char*> imageFace = {IMAGE_PATH"skybox/right.jpg",IMAGE_PATH"skybox/left.jpg" ,IMAGE_PATH"skybox/top.jpg" ,IMAGE_PATH"skybox/bottom.jpg" ,IMAGE_PATH"skybox/back.jpg" ,IMAGE_PATH"skybox/front.jpg" };

	unsigned char* image;
	for (unsigned int i = 0; i < imageFace.size(); i++)
	{
		image = SOIL_load_image(imageFace[i], &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image); 
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
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