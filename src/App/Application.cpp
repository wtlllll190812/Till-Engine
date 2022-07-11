#include "Application.h"
#include "GameLoop.h"
#include "Scene.h"
#include "Debug.h"
#include "EditorLayer.h"
#include "LayerStack.h"
#include <string>
using namespace std;
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include "Input.h"
#include <cmath>
#include "TLTime.h"
//临时
#include "GameObject.h"
#include "Material.h"
#include "Renderer.h"
#include "Transform.h"
#include "Scene.h"
#include "Camera.h"
#include "Light.h"
#include "TLEngineCG.h"
#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>
#include "Texture.h"
#include "imgui.h"


Application::Application()
{
	Debug::Init();
	mWindows = unique_ptr<Window>(Window::Create());
	mainLoop = shared_ptr<GameLoop>(new GameLoop(10));
	mLayerStack = shared_ptr<LayerStack>(new LayerStack());
	currentScene = shared_ptr<Scene>(new Scene(DATA_PATH "test.xml"));
	editorLayer = new EditorLayer(currentScene);
}

Application::~Application()
{
	delete editorLayer;
}

inline void Application::PushLayer(Layer *layer)
{
	mLayerStack->PushLayer(layer);
}

inline void Application::PushOverlay(Layer *layer)
{
	mLayerStack->PushOverlay(layer);
}

void Application::Init()
{
	mWindows->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	PushOverlay(editorLayer);
	Input::Init();
}

void Application::Run()
{
	Init();

	auto cameraObject = currentScene->Find("camera");
	auto object = currentScene->Find("object");
	Camera *camera = editorLayer->GetEditorCamera();
	shared_ptr<Material> mat = object->GetComponent<Renderer>()->material;
	Light *light = TLEngineCG::lights[0];


	mat->shader->Use();
	Texture tex(IMAGE_PATH"container.png");
	Texture specTex(IMAGE_PATH"container_specular.png");
	glUniform1i(glGetUniformLocation(mat->shader->Program, "diffuseMap"), 0);
	glUniform1i(glGetUniformLocation(mat->shader->Program, "specularMap"), 1);

	mat->SetRenderCallback([&cameraObject, object, camera, light, this, tex, specTex](GameObject *gameobject, Shader *shader, Material *mat)
						   {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex.texture); 
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, specTex.texture);			


			glEnable(GL_DEPTH_TEST);
			//gameobject->owner->camera;
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
		});
	mainLoop->SetUpdateCallback([&object, this]()
								{
			Input::Update();
			mWindows->OnRender();

			for (auto layer : *mLayerStack)
			{
				layer->OnUpdate();
			}
			/*object->transform->rotation.y = std::cos(TLTime::GetTime());
			object->transform->rotation.x = std::sin(TLTime::GetTime());*/
			mWindows->OnRenderEnd(); });
	Debug::GetAppLogger()->info("start loop");
	mainLoop->StartLoop();
}

void Application::OnEvent(EventBase &e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowsClose));

	for (auto it = (*mLayerStack).end(); it != (*mLayerStack).begin();)
	{
		(*--it)->OnEvent(e);
		if (e.mHandled)
			break;
	}
}

bool Application::OnWindowsClose(WindowCloseEvent &e)
{
	mRunning = false;
	return true;
}