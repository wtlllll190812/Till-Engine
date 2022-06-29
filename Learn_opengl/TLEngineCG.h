#pragma once
#include<glm/glm.hpp>
#include<vector>
#include<queue>
#include"Reflection.h"
enum class RendererQueue
{
	Background = 1000,
	Geometry = 2000,
	AlphaTest = 2450,
	Transparent = 3000,
	Overlay = 4000
};
class Light;
class Renderer;
class TLEngineCG
{
public:
	TLEngineCG();
	~TLEngineCG();

	static std::vector<Light*> lights;
};


#ifndef SetUniformMat4(matName,shaderName)	
#define SetUniformMat4(matName,shaderName)													\
			GLint matName##Loc = glGetUniformLocation(shaderName->Program, #matName);		\
			glUniformMatrix4fv(matName##Loc, 1, GL_FALSE, glm::value_ptr(matName));
#endif 


#ifndef SetUniformVec3(vecName,shaderName)	
#define SetUniformVec3(vecName,shaderName)													\
			GLint vecName##Loc = glGetUniformLocation(shaderName->Program, #vecName);		\
			glUniform3f(vecName##Loc, vecName.x, vecName.y, vecName.z);
#endif 