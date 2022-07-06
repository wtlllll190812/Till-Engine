#include "Application.h"
#include "GameLoop.h"
#include "Scene.h"
#include "ImguiLayer.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
#include "imgui.h"
#include "GuiWindow.h"
#include "Scene.h"
#include "GameObject.h"
#include "Debug.h"
#include "FrameBuffer.h"
#include <string>
using namespace std;

//临时
#include "Component.h"


Application::Application()
{
	Debug::Init();
	mWindows = unique_ptr<Window>(Window::Create());
	mainLoop = shared_ptr<GameLoop>(new GameLoop(10));;
	editorLayer = new ImguiLayer();
	mWindows->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
}

Application::~Application()
{
}

void Application::Init()
{
	PushOverlay(editorLayer);
	EditorInit();
	currentScene = shared_ptr<Scene>(new Scene(DATA_PATH "test.xml"));
}

void Application::Run()
{
	mWindows->OnRender();
	for (auto layer : mLayerStack)
	{
		layer->OnUpdate();
	}
	mWindows->OnRenderEnd();
}

void Application::OnEvent(EventBase& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowsClose));

	for (auto it = mLayerStack.end(); it != mLayerStack.begin();)
	{
		(*--it)->OnEvent(e);
		if (e.mHandled)
			break;
	}
}

void Application::EditorInit()
{
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
	editorLayer->RegisterGuiWindow(Docking);

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
	editorLayer->RegisterGuiWindow(Editor);

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
	editorLayer->RegisterGuiWindow(Hierarchy);

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
	editorLayer->RegisterGuiWindow(Inspector);

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
	editorLayer->RegisterGuiWindow(Console);

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
	editorLayer->RegisterGuiWindow(SceneView);
}

bool Application::OnWindowsClose(WindowCloseEvent& e)
{
	mRunning = false;
	return true;
}