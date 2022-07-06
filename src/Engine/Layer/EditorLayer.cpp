#include "EditorLayer.h"
#include "imgui.h"
#include "GuiWindow.h"
#include "Application.h"
#include "Scene.h"
#include "GameObject.h"
#include "Debug.h"
#include "FrameBuffer.h"
#include "Component.h"
#include "Camera.h"
#include <string>
using namespace std;

#include "Transform.h"
#include "Input.h"
#include "GLFW/glfw3.h"
EditorLayer::EditorLayer(std::shared_ptr<Scene> s)
{
	currentScene = s;
	editorCamera = shared_ptr<GameObject>(new GameObject());
	editorCamera->AddComponent(new Camera());

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
			ImGui::End(); },
		"sdsd"));
	RegisterGuiWindow(Docking);

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
	RegisterGuiWindow(Editor);

	auto Hierarchy = shared_ptr<GuiWindow>(new GuiWindow([this]()
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
	RegisterGuiWindow(Hierarchy);

	auto Inspector = shared_ptr<GuiWindow>(new GuiWindow([this]()
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
	RegisterGuiWindow(Inspector);

	auto Console = shared_ptr<GuiWindow>(new GuiWindow([]()
		{
			static bool Console = true;
			static vector<string> logBuffer;
			if (Console)
			{
				ImGui::Begin("Console", &Console);
				string str;
				while (std::getline(Debug::appLogOss, str))
				{
					logBuffer.push_back(str);
				}

				for (auto& s : logBuffer)
					ImGui::BulletText(s.c_str());

				ImGui::End();
			} },
		"Console"));
	RegisterGuiWindow(Console);

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
				auto fb = Application::instance().mWindows->GetFrameBuffer();
				ImGui::Image((ImTextureID)fb->GetFBO(), wsize, ImVec2(0, 1), ImVec2(1, 0));
				fb->Resize(wsize.x, wsize.y);
				ImGui::EndChild();
			}
			ImGui::End();
		},
		"SceneView"));
	RegisterGuiWindow(SceneView);
}

EditorLayer::~EditorLayer()
{
}

void EditorLayer::OnUpdate()
{
	RenderStart();

	//ImGui::ShowDemoWindow();
	for (std::shared_ptr<GuiWindow> i : uiWindows)
	{
		i->Render();
	}
	if (Input::GetKeyDown(GLFW_KEY_W))
		editorCamera->transform->Translate(0.1f);
	if (Input::GetKeyDown(GLFW_KEY_S))
		editorCamera->transform->Translate(-0.1f);
	if (Input::GetKeyDown(GLFW_KEY_A))
		editorCamera->transform->Translate(editorCamera->transform->GetRight(), -0.1f);
	if (Input::GetKeyDown(GLFW_KEY_D))
		editorCamera->transform->Translate(editorCamera->transform->GetRight(), 0.1f);
	if (currentObj != nullptr)
	{
		if (Input::GetKeyDown(GLFW_KEY_RIGHT))
			currentObj->transform->rotation.z += 0.05f;
		if (Input::GetKeyDown(GLFW_KEY_LEFT))
			currentObj->transform->rotation.z -= 0.05f;
		if (Input::GetKeyDown(GLFW_KEY_UP))
			currentObj->transform->rotation.x += 0.05f;
		if (Input::GetKeyDown(GLFW_KEY_DOWN))
			currentObj->transform->rotation.x -= 0.05f;
	}
	RenderEnd();
}

void EditorLayer::SetScene(Scene* s)
{
}

Camera* EditorLayer::GetEditorCamera()
{
	return editorCamera->GetComponent<Camera>();
}
