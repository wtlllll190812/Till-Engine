#include "PostprocessLayer.h"
#include "Shader.h"
#include "TLCore.h"
#include "Debug.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include "Application.h"
#include "Texture.h"

PostprocessLayer::PostprocessLayer(FrameBuffer* _buffer):buffer(_buffer)
{
	shader = new Shader(SHADER_PATH"postprocess.vert", SHADER_PATH"postprocess.frag");
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
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, Application::instance().mWindows->GetMianFrameBuffer()->GetColorBuffer()->texture);
	/*if (!inited)
	{
		Init(object, mesh);
		inited = true;
	}
	glBindVertexArray(mesh->VAO);
	shader->Use();
	DrawFunc(object, mesh);
	glDrawElements(GL_TRIANGLES, mesh->GetSize(), GL_UNSIGNED_INT, 0);
	glDepthMask(GL_TRUE);
	glCullFace(GL_BACK);
	glBindVertexArray(0);*/
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