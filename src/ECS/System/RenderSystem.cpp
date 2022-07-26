#include"RenderSystem.h"
#include"Renderer.h"
#include"Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include "TLEngineCG.h"
#include "Light.h"
#include "GameObject.h"
#include "Transform.h"
#include "Debug.h"
#include "Application.h"
#include "Window.h"
#include "Material.h"


#include "AssetImporter.h"
typedef std::priority_queue <Renderer*, std::vector<Renderer*>> renderPriorityQueue;
renderPriorityQueue RenderSystem::renderQueue = renderPriorityQueue();
std::shared_ptr<Mesh> skybox;

RenderSystem::RenderSystem()
{
	maticesUB.BufferInit(sizeof(glm::mat4) * 2);
	mainLightUB.BufferInit(sizeof(glm::vec3) * 3);
	skybox = AssetImporter::LoadMeshs(MODEL_PATH"Cube/Cube.obj")[0];
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::Update()
{
	renderPriorityQueue queue = renderQueue;

	RenderShadow(queue);
	SetData();

	queue = renderQueue;
	TLEngineCG::skyboxMat->Draw(nullptr,skybox);
	while (!queue.empty())
	{
		if (queue.top() != nullptr)
		{
			queue.top()->Draw();
			queue.pop();
		}
	}
}

void RenderSystem::SetData()
{
	//Set MVP Matices
	maticesUB.SetData(sizeof(glm::mat4), 0, glm::value_ptr(currentCamera->GetProjMatrix()));
	maticesUB.SetData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(currentCamera->GetViewMatrix()));

	//Set Light Data
	Light* light = TLEngineCG::lights[0];
	mainLightUB.SetData(sizeof(glm::vec3), 0, glm::value_ptr(light->gameobject->transform->GetFront()));//glm::value_ptr(light->gameobject->transform->position));
	mainLightUB.SetData(sizeof(glm::vec3), 16, glm::value_ptr(light->color));
	mainLightUB.SetData(sizeof(glm::vec3), 32, glm::value_ptr(currentCamera->gameobject->transform->position));
}

void RenderSystem::RenderShadow(renderPriorityQueue queue)
{
	auto& window = Application::instance().mWindows;
	window->SetFrameBuffer(TLEngineCG::shadowBuffer);
	glCullFace(GL_FRONT);
	while (!queue.empty())
	{
		if (queue.top() != nullptr)
		{
			TLEngineCG::sadowCaster->Draw(queue.top()->gameobject, queue.top()->mesh);
			queue.pop();
		}
	}
	glCullFace(GL_BACK);
	window->SetFrameBuffer(window->GetMianFrameBuffer());
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

void RenderSystem::Clear()
{
	renderQueue = renderPriorityQueue();
}