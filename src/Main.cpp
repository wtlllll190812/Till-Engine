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
#include "GuiWindow.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "WindowsWindow.h"
#include "TillPch.h"
#include "Application.h"
#include "ImguiLayer.h"

#define DATA_PATH "../data/"
#define SHADER_PATH "../shaders/"
#define IMAGE_PATH "../resource/"

Scene* currentScene;
std::shared_ptr<GameObject> currentObj;

Camera* camera;
shared_ptr<GameObject> cameraObject;
shared_ptr<GameObject> object;
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
	// 场景初始化
	currentScene = new Scene(DATA_PATH "test.xml");
	cameraObject = currentScene->Find("camera");
	object = currentScene->Find("object");
	camera = cameraObject->GetComponent<Camera>();
}

int smain()
{
	Debug::Init();
	Debug::GetEngineLogger()->info("Engine Init");
	Init();
	Debug::GetEngineLogger()->info("Engine Inited");



	shared_ptr<Material> mat = object->GetComponent<Renderer>()->material;
	// 绑定回调函数
	// glfwSetKeyCallback(Screen::instance().window, key_callback);
	// glfwSetCursorPosCallback(Screen::instance().window, mouse_callback);
	// glfwSetScrollCallback(Screen::instance().window, scroll_callback);

	mat->SetRenderCallback([](GameObject* gameobject, Shader* shader, Material* mat)
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

			glDrawArrays(GL_TRIANGLES, 0, 36); });

	loop.SetUpdateCallback(fixedupdate); /*[]()
		 {
		 });*/

	loop.SetFixedUpdateCallback([]()
		{ do_movement(); });

	loop.StartLoop();

	return 0;
}

int main()
{
	Debug::Init();
	Application::instance().Init();

	//临时

	auto guiLayer = Application::instance().GetGuiLayer();
	
	auto Docking = shared_ptr<GuiWindow>(new GuiWindow([]()
		{
			bool p_open = true;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode;

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;

			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			window_flags |= ImGuiWindowFlags_NoBackground;

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("DockSpace Demo", &p_open, window_flags);
			ImGui::PopStyleVar();

			ImGui::PopStyleVar(2);

			// Submit the DockSpace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			//if (ImGui::BeginMenuBar())
			//{
			//	if (ImGui::BeginMenu("Options"))
			//	{
			//		// Disabling fullscreen would allow the window to be moved to the front of other windows,
			//		// which we can't undo at the moment without finer window depth/z control.
			//		ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
			//		ImGui::MenuItem("Padding", NULL, &opt_padding);
			//		ImGui::Separator();

			//		if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
			//		if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
			//		if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
			//		if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
			//		if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
			//		ImGui::Separator();

			//		if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
			//			p_open = false;
			//		ImGui::EndMenu();
			//	}

			//	ImGui::EndMenuBar();
			//}

			ImGui::End(); },
		"sdsd"));
	guiLayer->RegisterGuiWindow(Docking);

	auto Editor = shared_ptr<GuiWindow>(new GuiWindow([]()
		{
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
			} },
		"Editor"));
	guiLayer->RegisterGuiWindow(Editor);

	auto Hierarchy = shared_ptr<GuiWindow>(new GuiWindow([]()
		{
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
			} },
		"Hierarchy"));
	guiLayer->RegisterGuiWindow(Hierarchy);

	auto Inspector = shared_ptr<GuiWindow>(new GuiWindow([]()
		{
			static bool Inspector = true;
			if (Inspector)
			{
				ImGui::Begin("Inspector", &Inspector);
				if (currentObj != nullptr)
				{
					for (auto i : currentObj->components)
					{
						if (ImGui::CollapsingHeader(i->GetName().c_str()))
						{
						}
					}
				}
				ImGui::End();
			} },
		"Inspector"));
	guiLayer->RegisterGuiWindow(Inspector);

	auto Console = shared_ptr<GuiWindow>(new GuiWindow([]()
		{
			static bool Console = true;
			static vector<string> logBuffer;
			if (Console)
			{
				ImGui::Begin("Console", &Console);
				string str;
				while (getline(Debug::appLogOss, str))
				{
					logBuffer.push_back(str);
				}

				for (auto& s : logBuffer)
					ImGui::BulletText(s.c_str());

				ImGui::End();
			} },
		"Console"));
	guiLayer->RegisterGuiWindow(Console);	
	
	auto SceneView = shared_ptr<GuiWindow>(new GuiWindow([]()
		{
			ImGui::Begin("Scene");
			{
				// Using a Child allow to fill all the space of the window.
				// It also alows customization
				ImGui::BeginChild("GameRender");
				// Get the size of the child (i.e. the whole draw size of the windows).
				ImVec2 wsize = ImGui::GetWindowSize();
				// Because I use the texture from OpenGL, I need to invert the V from the UV.
				GLuint* x = (GLuint*)Application::instance().mWindows->GetFrameBuffer();
				Debug::GetAppLogger()->info(*x);
				ImGui::Image((ImTextureID)(*x), wsize, ImVec2(0, 1), ImVec2(1, 0));
				ImGui::EndChild();
			}
			ImGui::End();
		},
		"SceneView"));
	guiLayer->RegisterGuiWindow(SceneView);

	Application::instance().mWindows->SetFrameBuffer();
	Texture* tex = new Texture();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex->texture, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// 场景初始化
	currentScene = new Scene(DATA_PATH "test.xml");
	cameraObject = currentScene->Find("camera");
	object = currentScene->Find("object");
	camera = cameraObject->GetComponent<Camera>();
	shared_ptr<Material> mat = object->GetComponent<Renderer>()->material;
	mat->SetRenderCallback([](GameObject* gameobject, Shader* shader, Material* mat)
		{
			Application::instance().mWindows->SetFrameBuffer();
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
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		});

	GameLoop loop(60);
	loop.SetUpdateCallback([]()
		{
			Application::instance().Run();
		});
	Debug::GetAppLogger()->info("start loop");
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

	GLfloat sensitivity = 0.05; // Change this value to your liking
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