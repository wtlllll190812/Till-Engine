#include "Camera.h"
#include "Transform.h"
#include "Texture.h"
#include "Shader.h"
#include "Light.h"
#include "Renderer.h"
#include "Material.h"
#include "TLEngineCG.h"
#include "GameLoop.h"
#include "RenderSystem.h"

#include "TLEngineCG.h"
#include "Debug.h"
#include "GuiWindow.h"
#include <glm/gtc/type_ptr.hpp>
#include "WindowsWindow.h"
#include "Application.h"
#include "ImguiLayer.h"
#include "Input.h"
#include "GameObject.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>

Camera* camera;
shared_ptr<GameObject> cameraObject;
shared_ptr<GameObject> object;
GameLoop loop(60);

int main()
{
	Application::instance().Init();
	//临时

	// 场景初始化
	/*cameraObject = currentScene->Find("camera");
	object = currentScene->Find("object");
	camera = cameraObject->GetComponent<Camera>();
	shared_ptr<Material> mat = object->GetComponent<Renderer>()->material;
	mat->SetRenderCallback([](GameObject* gameobject, Shader* shader, Material* mat)
		{
			glEnable(GL_DEPTH_TEST);
			mat->renderQueueIndex = (int)RendererQueue::Background;
			glm::vec3 viewPos = cameraObject->transform->position;

			glm::mat4 view = gameobject->owner->camera->GetViewMatrix();
			glm::mat4 projection = gameobject->owner->camera->GetProjMatrix();
			glm::mat4 model = object->transform->GetModel();

			Light* light = TLEngineCG::lights[0];
			glm::vec3 lightPos = light->gameobject->GetComponent<Transform>()->position;
			glm::vec3 lightColor = light->color;
			glm::vec3 objectColor(1.0f, 0.5f, 0.31f);

			SetUniformMat4(view, shader);
			SetUniformMat4(projection, shader);
			SetUniformMat4(model, shader);

			SetUniformVec3(lightPos, shader);
			SetUniformVec3(objectColor, shader);
			SetUniformVec3(lightColor, shader);
			SetUniformVec3(viewPos, shader);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		});*/

	GameLoop loop(60);
	loop.SetUpdateCallback([]()
		{
			Application::instance().Run();
			if (Input::GetKeyDown(GLFW_KEY_W))
				cameraObject->transform->Translate(0.05f);
			if (Input::GetKeyDown(GLFW_KEY_S))
				cameraObject->transform->Translate(-0.05f);
			if (Input::GetKeyDown(GLFW_KEY_A))
				cameraObject->transform->Translate(cameraObject->transform->GetRight(), -0.05f);
			if (Input::GetKeyDown(GLFW_KEY_D))
				cameraObject->transform->Translate(cameraObject->transform->GetRight(), 0.05f);
			if (Input::GetKeyDown(GLFW_KEY_RIGHT))
				object->transform->rotation.z += 0.05f;
			if (Input::GetKeyDown(GLFW_KEY_LEFT))
				object->transform->rotation.z -= 0.05f;
			if (Input::GetKeyDown(GLFW_KEY_UP))
				object->transform->rotation.x += 0.05f;
			if (Input::GetKeyDown(GLFW_KEY_DOWN))
				object->transform->rotation.x -= 0.05f;
		});
	Debug::GetAppLogger()->info("start loop");
	loop.StartLoop();
	return 0;
}
