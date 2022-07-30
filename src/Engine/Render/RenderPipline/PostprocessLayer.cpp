#include "PostprocessLayer.h"
#include "Shader.h"

PostprocessLayer::PostprocessLayer()
{
	shader = new Shader("","");
}

PostprocessLayer::~PostprocessLayer()
{
}

void PostprocessLayer::OnAttack()
{
}

void PostprocessLayer::OnDetach()
{
}

void PostprocessLayer::OnUpdate()
{
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