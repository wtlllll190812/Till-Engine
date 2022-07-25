#include "MatDefault.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include "Reflection.h"
#include "Texture.h"
#include "GameObject.h"
#include "Transform.h"
#include "Application.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "RenderSystem.h"

REFLECTIONINSTANCE(DefaultMaterial, Material);
#include "Light.h"
DefaultMaterial::DefaultMaterial()
{
	shader = new Shader(SHADER_PATH"default.vert", SHADER_PATH"default.frag");
	mainTex=new Texture(IMAGE_PATH"ground_diff.jpg");
	specTex=new Texture(IMAGE_PATH"ground_spec.jpg");
	matName = "DefaultMaterial";
}

DefaultMaterial::~DefaultMaterial()
{
	delete shader;
	delete mainTex;
	delete specTex;
}

void DefaultMaterial::DrawFunc(GameObject* gObj, std::shared_ptr<Mesh> mesh)
{
	renderQueueIndex = (int)RendererQueue::Background;

	unsigned int ShadowTex = TLEngineCG::shadowBuffer->GetDepthBuffer()->texture;
	
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, ShadowTex);

	glm::mat4 lightSpaceMat = TLEngineCG::lights[0]->GetOrthoMatrix() * TLEngineCG::lights[0]->GetViewMatrix();
	glm::mat4 model = gObj->transform->GetModelMatrix();
	glm::vec3 objectColor(1.0f, 1.0f, 1.0f);

	SetUniformMat4(lightSpaceMat, shader);
	SetUniformMat4(model, shader);
	SetUniformVec3(objectColor, shader);
}

void DefaultMaterial::Init(GameObject*, std::shared_ptr<Mesh> mesh)
{
	shader->Use();
	glUniform1i(glGetUniformLocation(shader->Program, "diffuseMap"), 0);
	glUniform1i(glGetUniformLocation(shader->Program, "specularMap"), 1);
	glUniform1i(glGetUniformLocation(shader->Program, "shadowMap"), 2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mainTex->texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specTex->texture);
	//设定Ubo绑定节点
	unsigned int mat = glGetUniformBlockIndex(shader->Program, "Matrices");
	glUniformBlockBinding(shader->Program, mat, 0);	
	mat = glGetUniformBlockIndex(shader->Program, "LightData");
	glUniformBlockBinding(shader->Program, mat, 1);

}