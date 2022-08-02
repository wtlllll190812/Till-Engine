#include "PostprocessLayer.h"
#include "Shader.h"
#include "TLCore.h"
#include "Debug.h"
#include "Mesh.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include "Application.h"
#include "Texture.h"

std::shared_ptr<Mesh> PostprocessLayer::quadMesh;

PostprocessLayer::PostprocessLayer(FrameBuffer* _buffer):buffer(_buffer)
{
	shader = new Shader(SHADER_PATH"postprocess.vert", SHADER_PATH"postprocess.frag");
	quadMesh = std::make_shared<Mesh>();
}

PostprocessLayer::~PostprocessLayer()
{
	delete shader;
}

void PostprocessLayer::OnAttack()
{
	shader->Use();
	glUniform1i(glGetUniformLocation(shader->Program, "screenTexture"), 4);
	
}

void PostprocessLayer::OnDetach()
{
}

void PostprocessLayer::OnUpdate()
{
	shader->Use();
	glBindVertexArray(quadMesh->VAO);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, Application::instance().mWindows->GetMianFrameBuffer()->GetColorBuffer()->texture);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

float PostprocessLayer::quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
};