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
	/// <summary>
	/// 场景中所有的灯
	/// </summary>
	static std::vector<Light*> lights;
	
	/// <summary>
	/// 深度缓冲
	/// </summary>
	static FrameBuffer* shadowMap;

	/// <summary>
	/// 场景主光源
	/// </summary>
	static Light* mainLight;
	
	/// <summary>
	/// 用于投射阴影的材质
	/// </summary>
	static Material* sadowCaster;

	/// <summary>
	/// 用于渲染天空盒的材质
	/// </summary>
	static Material* skyboxMat;
public:

	/// <summary>
	/// 注册光源
	/// </summary>
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
