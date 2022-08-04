#include "MatPBR.h"

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
#include "Light.h"

REFLECTIONINSTANCE(MatPBR, Material);
MatPBR::MatPBR()
{
	shader = new Shader(SHADER_PATH"PBRbase.vert", SHADER_PATH"PBRbase.frag");
	matName = "MatPBR";
}

MatPBR::~MatPBR()
{
}

void MatPBR::DrawFunc(GameObject* gObj, std::shared_ptr<Mesh> mesh)
{
	renderQueueIndex = (int)RendererQueue::Background;

	glm::mat4 lightSpaceMat = TLEngineCG::lights[0]->GetOrthoMatrix() * TLEngineCG::lights[0]->GetViewMatrix();
	glm::mat4 model = gObj->transform->GetModelMatrix();

	glUniform1f(glGetUniformLocation(shader->Program, "metallic"), metallic);
	glUniform1f(glGetUniformLocation(shader->Program, "roughness"), roughness);
	glUniform1f(glGetUniformLocation(shader->Program, "ao"), ao);

	SetUniformMat4(lightSpaceMat, shader);
	SetUniformMat4(model, shader);
	SetUniformVec3(albedo, shader);
}

void MatPBR::Init(GameObject*, std::shared_ptr<Mesh> mesh)
{
	shader->Use();
	//设定Ubo绑定节点
	unsigned int mat = glGetUniformBlockIndex(shader->Program, "Matrices");
	glUniformBlockBinding(shader->Program, mat, 0);
	mat = glGetUniformBlockIndex(shader->Program, "LightData");
	glUniformBlockBinding(shader->Program, mat, 1);
}

void MatPBR::GuiDisPlay()
{
	ImGui::ColorEdit3("albedo", glm::value_ptr(albedo));
	ImGui::DragFloat("metallic", &metallic,0.001,0,1);
	ImGui::DragFloat("roughness", &roughness, 0.001, 0, 1);
	ImGui::DragFloat("ao", &ao, 0.001, 0, 1);
}
