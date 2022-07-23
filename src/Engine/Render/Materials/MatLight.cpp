#include "MatLight.h"
#include "Shader.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "GameObject.h"
#include "Transform.h"
#include "Reflection.h"

REFLECTIONINSTANCE(LightMaterial,Material);

LightMaterial::LightMaterial()
{
	shader = new Shader(SHADER_PATH"light.vert", SHADER_PATH"light.frag");
	matName = "LightMaterial";
}

LightMaterial::~LightMaterial()
{
	delete shader;
}

void LightMaterial::DrawFunc(GameObject* gObj, std::shared_ptr<Mesh> mesh)
{
	renderQueueIndex = (int)RendererQueue::Background;

	glm::mat4 model = gObj->transform->GetModelMatrix();
	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

	SetUniformMat4(model, shader);
	SetUniformVec3(lightColor, shader);
}

void LightMaterial::Init(GameObject*, std::shared_ptr<Mesh> mesh)
{
	shader->Use();
	glUniform1i(glGetUniformLocation(shader->Program, "diffuseMap"), 0);
	glUniform1i(glGetUniformLocation(shader->Program, "specularMap"), 1);

	//设定Ubo绑定节点
	unsigned int mat = glGetUniformBlockIndex(shader->Program, "Matrices");
	glUniformBlockBinding(shader->Program, mat, 0);
	mat = glGetUniformBlockIndex(shader->Program, "LightData");
	glUniformBlockBinding(shader->Program, mat, 1);
}
