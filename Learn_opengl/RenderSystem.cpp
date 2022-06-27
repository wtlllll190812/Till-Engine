#include"RenderSystem.h"
#include"Renderer.h"

std::priority_queue <Renderer*, std::vector<Renderer*>> renderQueue = std::priority_queue < Renderer*, std::vector<Renderer*>>();

void RenderSystem::Update()
{
}

void RenderSystem::FixedUpdate()
{
	while (!renderQueue.empty())
	{
		if (renderQueue.top() != nullptr)
		{
			renderQueue.top()->Render();
			renderQueue.pop();
		}
	}
}

void RenderSystem::RegisterComponent(Component* com)
{
	renderQueue.push(dynamic_cast<Renderer*>(com));
}

void RenderSystem::RemoveComponent(Component* com)
{
}