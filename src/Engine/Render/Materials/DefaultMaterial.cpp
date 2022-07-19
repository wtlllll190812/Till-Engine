#include "DefaultMaterial.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "Reflection.h"
#include "TLCore.h"
#include "Texture.h"
#include "GameObject.h"
#include "Transform.h"
#include "Application.h"
#include "Shader.h"

REFLECTION(DefaultMaterial,Material);

DefaultMaterial::DefaultMaterial()
{
	shader = new Shader(SHADER_PATH"default.vert", SHADER_PATH"default.frag");
	tex=new Texture(IMAGE_PATH"container.png");
	specTex=new Texture(IMAGE_PATH"container_specular.png");
	matName = "DefaultMaterial";
}

DefaultMaterial::~DefaultMaterial()
{
	delete shader;
	delete tex;
	delete specTex;
}

void DefaultMaterial::OnRender(GameObject* gObj, std::shared_ptr<Mesh> mesh)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex->texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specTex->texture);

	renderQueueIndex = (int)RendererQueue::Background;

	glm::mat4 model = gObj->transform->GetModelMatrix();
	glm::vec3 objectColor(1.0f, 1.0f, 1.0f);

	SetUniformMat4(model, shader);
	SetUniformVec3(objectColor, shader);
}

void DefaultMaterial::BeforeRender(GameObject*, std::shared_ptr<Mesh> mesh)
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