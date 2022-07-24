#include "MatShadowCaster.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include "Reflection.h"
#include "GameObject.h"
#include "Transform.h"
#include "Application.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "Light.h"
#include "RenderSystem.h"

#include "Camera.h"
MatShadowCaster::MatShadowCaster()
{
	shader = new Shader(SHADER_PATH"shadowCaster.vert", SHADER_PATH"shadowCaster.frag");
	matName = "MatShadowCaster";
}

MatShadowCaster::~MatShadowCaster()
{
	
}

void MatShadowCaster::DrawFunc(GameObject* gObj, std::shared_ptr<Mesh> mesh)
{
	shader->Use();
	glm::mat4 lightSpaceMat = TLEngineCG::lights[0]->GetOrthoMatrix() *TLEngineCG::lights[0]->GetViewMatrix();
	glm::mat4 model = gObj->transform->GetModelMatrix();
	SetUniformMat4(lightSpaceMat, shader);
	SetUniformMat4(model, shader);
}

void MatShadowCaster::Init(GameObject*, std::shared_ptr<Mesh> mesh)
{
}
