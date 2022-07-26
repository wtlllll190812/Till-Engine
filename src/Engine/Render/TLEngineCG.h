#pragma once
#include <vector>
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
class FrameBuffer;
class Material;
class Texture;
class TLEngineCG
{
public:
	static FrameBuffer* shadowBuffer;
	static std::vector<Light*> lights;
	static Light* mainLight;
	static Material* sadowCaster;
	static Material* skyboxMat;
public:
	static void AddLight(Light* l);
};

#ifndef SetUniformMat4
#define SetUniformMat4(matName, shaderName)                                   \
	GLint matName##Loc = glGetUniformLocation(shaderName->Program, #matName); \
	glUniformMatrix4fv(matName##Loc, 1, GL_FALSE, glm::value_ptr(matName));
#endif

#ifndef SetUniformVec3
#define SetUniformVec3(vecName, shaderName)                                   \
	GLint vecName##Loc = glGetUniformLocation(shaderName->Program, #vecName); \
	glUniform3f(vecName##Loc, vecName.x, vecName.y, vecName.z);
#endif

#ifndef SetUniformTex
#define SetUniformTex(texName, index, shaderName)  \
	glActiveTexture(GL_TEXTURE##index);            \
	glBindTexture(GL_TEXTURE_2D, texName.texture); \
	glUniform1i(glGetUniformLocation(shaderName->Program, #texName), index);
#endif
