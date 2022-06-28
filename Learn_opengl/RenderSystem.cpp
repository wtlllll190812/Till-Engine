#include"RenderSystem.h"
#include"Renderer.h"
#include<iostream>

typedef std::priority_queue <Renderer*, std::vector<Renderer*>> renderPriorityQueue;
renderPriorityQueue renderQueue = renderPriorityQueue();

RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::Update()
{
	renderPriorityQueue queue = renderQueue;
	while (!queue.empty())
	{
		if (queue.top() != nullptr)
		{
			std::cout << queue.top()->guid << std::endl;
			queue.top()->Render();
			queue.pop();
		}
	}
}

void RenderSystem::FixedUpdate()
{
	
}

void RenderSystem::RegisterComponent(Component* com)
{
	renderQueue.push(dynamic_cast<Renderer*>(com));
}

void RenderSystem::RemoveComponent(Component* com)
{
}