#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include<sstream>

#include "Screen.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Texture.h"
#include "Shader.h"
#include "Light.h"
#include "Renderer.h"
#include "Material.h"
#include "TLEngineCG.h"
#include "GameLoop.h"
#include "RenderSystem.h"
#include "Scene.h"
#include "TLEngineCG.h"
#include "Debug.h"
#include "GuiWindows.h"


Scene* currentScene;
GameObject* currentObj;

Camera* camera;
GameObject* cameraObject;
GameObject* object;
GameLoop loop(60);

bool keys[1024];

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();
void fixedupdate()
{
	Screen::instance().Display();
	RenderSystem::instance().Update();
	Screen::instance().GuiRender();
	glfwSwapBuffers(Screen::instance().window);
}

void Init()
{

	//窗口注册
	auto Editor = shared_ptr<GuiWindows>(new GuiWindows([]() {
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("TODO")) {
					//do something
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
		}, "Editor"));
	Screen::instance().RegisterGuiWindows(Editor);

	auto Hierarchy = shared_ptr<GuiWindows>(new GuiWindows([]() {
		static bool hierarchy = true;
		if (hierarchy)
		{
			ImGui::Begin("Hierarchy", &hierarchy);
			if (currentScene != nullptr)
			{
				if (ImGui::CollapsingHeader("Window options"))
				{
					for (auto i : currentScene->gameobjects)
					{
						if (ImGui::Button(i->name.c_str())) {
							currentObj = i;
						}
					}
				}
			}
			ImGui::End();
		}
		}, "Hierarchy"));
	Screen::instance().RegisterGuiWindows(Hierarchy);

	auto Inspector = shared_ptr<GuiWindows>(new GuiWindows([]() {
		static bool Inspector = true;
		if (Inspector)
		{
			ImGui::Begin("Inspector", &Inspector);
			if (currentObj != nullptr)
			{
				for (auto i : currentObj->components)
				{
					if (ImGui::CollapsingHeader(i->componentName.c_str()))
					{

					}
				}
			}
			ImGui::End();
		}
		}, "Inspector"));
	Screen::instance().RegisterGuiWindows(Inspector);

	auto Console = shared_ptr<GuiWindows>(new GuiWindows([]() {
		static bool Console = true;
		if (Console)
		{
			ImGui::Begin("Console", &Console);
			string s = Debug::appLogOss.str();
			ImGui::BulletText(s.c_str());
			ImGui::BulletText("bbb");
			ImGui::BulletText("ccc");

			ImGui::End();
		}
		}, "Console"));
	Screen::instance().RegisterGuiWindows(Console);
	

	// 场景初始化
	currentScene = new Scene("Data/test.xml");
	cameraObject = currentScene->Find("camera");
	object = currentScene->Find("object");
	camera = cameraObject->GetComponent<Camera>();
}

int main()
{
	Debug::Init();
	Debug::GetEngineLogger()->info("Engine Init");
	Init();
	Debug::GetEngineLogger()->info("Engine Inited");

	Debug::GetAppLogger()->warn("sdsd");

	shared_ptr<Material> mat = object->GetComponent<Renderer>()->material;
	// 绑定回调函数
	//glfwSetKeyCallback(Screen::instance().window, key_callback);
	//glfwSetCursorPosCallback(Screen::instance().window, mouse_callback);
	//glfwSetScrollCallback(Screen::instance().window, scroll_callback);

	mat->SetRenderCallback([](GameObject* gameobject,Shader* shader, Material* mat)
		{
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
		});

	loop.SetUpdateCallback(fixedupdate);/*[]()
		{
			
		});*/

	loop.SetFixedUpdateCallback([]()
		{
			do_movement();
		});
	
	loop.StartLoop();
	
	return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void do_movement()
{
	if (keys[GLFW_KEY_W])
		cameraObject->transform->Translate(0.05f);
	if (keys[GLFW_KEY_S])
		cameraObject->transform->Translate(-0.05f);
	if (keys[GLFW_KEY_A])
		cameraObject->transform->Translate(cameraObject->transform->GetRight(), -0.05f);
	if (keys[GLFW_KEY_D])
		cameraObject->transform->Translate(cameraObject->transform->GetRight(), 0.05f);
	if (keys[GLFW_KEY_RIGHT])
		object->transform->rotation.z += 0.05f;
	if (keys[GLFW_KEY_LEFT])
		object->transform->rotation.z -= 0.05f;	
	if (keys[GLFW_KEY_UP])
		object->transform->rotation.x += 0.05f;
	if (keys[GLFW_KEY_DOWN])
		object->transform->rotation.x -= 0.05f;
}

GLfloat lastX;
GLfloat lastY;
bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to left
	lastX = xpos;
	lastY = ypos;

	GLfloat sensitivity = 0.05;	// Change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	cameraObject->transform->rotation.x += xoffset;
	cameraObject->transform->rotation.z += yoffset;
	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (cameraObject->transform->rotation.z > 89.0f)
		cameraObject->transform->rotation.z = 89.0f;
	if (cameraObject->transform->rotation.z < -89.0f)
		cameraObject->transform->rotation.z = -89.0f;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (camera->fov >= 1.0f && camera->fov <= 45.0f)
		camera->fov -= yoffset;
	if (camera->fov <= 1.0f)
		camera->fov = 1.0f;
	if (camera->fov >= 45.0f)
		camera->fov = 45.0f;
}