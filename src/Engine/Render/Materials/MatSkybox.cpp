#include "MatSkybox.h"

#define GLFW_INCLUDE_NONE		
#include <GLFW/glfw3.h>			
#include <GL/glew.h>			

#include "Shader.h"				
#include "Texture.h"			
#include "TLEngineCG.h"			

#include "glm/glm.hpp"			
#include <glm/gtc/type_ptr.hpp> 


#include "RenderSystem.h"
#include "Camera.h"
MatSkybox::MatSkybox()
{
	shader = new Shader(SHADER_PATH"skybox.vert", SHADER_PATH"skybox.frag");
	skybox = new Texture(TextureType::Cube);
	matName = "MatSkybox";
}

MatSkybox::~MatSkybox()
{
	delete skybox;
}

void MatSkybox::DrawFunc(GameObject* gObj, std::shared_ptr<Mesh> mesh)
{
	glCullFace(GL_FRONT);
	glDepthFunc(GL_LEQUAL);
	shader->Use();
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->texture);

	glm::mat4 projection = RenderSystem::instance().currentCamera->GetProjMatrix();
	glm::mat4 view= glm::mat4(glm::mat3(RenderSystem::instance().currentCamera->GetViewMatrix()));
	SetUniformMat4(projection,shader);
	SetUniformMat4(view, shader);
}

void MatSkybox::Init(GameObject*, std::shared_ptr<Mesh> mesh)
{
	unsigned int mat = glGetUniformBlockIndex(shader->Program, "Matrices");
	glUniformBlockBinding(shader->Program, mat, 0);
}
