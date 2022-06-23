#include "Renderer.h"

Renderer::Renderer(Mesh* m, Material* mater, GameObject* g) :Component(g)
{
	mesh = m;
	material = mater;
}

Renderer::~Renderer()
{
}

void Renderer::Render()
{
	material->Render(mesh);
}

void Renderer::OnAdd()
{
	renderQueue.push(dynamic_cast<Renderer*>(this));
}