#include "DefaultMaterial.h"
#include "GLFW/glfw3.h"
#include "gl/glew.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "Reflection.h"


REFLECTION(DefaultMaterial,Material);

DefaultMaterial::DefaultMaterial()
{
	mat->shader->Use();
	Texture tex(IMAGE_PATH"container.png");
	Texture specTex(IMAGE_PATH"container_specular.png");
	glUniform1i(glGetUniformLocation(mat->shader->Program, "diffuseMap"), 0);
	glUniform1i(glGetUniformLocation(mat->shader->Program, "specularMap"), 1);
}

DefaultMaterial::~DefaultMaterial()
{
}

void DefaultMaterial::RenderCallback(GameObject*, Shader*, Material*)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex.texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specTex.texture);

	mat->renderQueueIndex = (int)RendererQueue::Background;
	glm::vec3 viewPos = camera->gameobject->transform->position;
	glm::vec3 spotLightDir = light->gameobject->transform->GetFront();

	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection = camera->GetProjMatrix();
	glm::mat4 model = object->transform->GetModelMatrix();

	glm::vec3 lightPos = light->gameobject->transform->position;
	glm::vec3 lightColor = light->color;
	glm::vec3 objectColor(1.0f, 1.0f, 1.0f);

	SetUniformMat4(view, shader);
	SetUniformMat4(projection, shader);
	SetUniformMat4(model, shader);

	SetUniformVec3(lightPos, shader);
	SetUniformVec3(objectColor, shader);
	SetUniformVec3(lightColor, shader);
	SetUniformVec3(viewPos, shader);
	SetUniformVec3(spotLightDir, shader);
}
