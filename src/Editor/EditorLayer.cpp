#include "EditorLayer.h"

#include "imgui.h"
#include "ImGuizmo.h"
#include "GuiWindow.h"
#include "Application.h"

#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"
#include "Scene.h"

#include "GLFW/glfw3.h"
#include "FrameBuffer.h"
#include "Debug.h"
#include "Input.h"
#include "Reflection.h"

#include <string>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
#include "TLEngineCG.h"
#include "Texture.h"
EditorLayer::EditorLayer(std::shared_ptr<Scene> s)
{
	mCurrentScene = s;
	editorCamera = shared_ptr<GameObject>(new GameObject());
	editorCamera->AddComponent(new Camera());
	Transform* tr = s->mainCamera->gameobject->transform;
	editorCamera->transform->position = tr->position;
	editorCamera->transform->rotation = tr->rotation;

	auto Menu = shared_ptr<GuiWindow>(new GuiWindow([this]()
		{
			if (ImGui::BeginMainMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Edit"))
				{
					if (ImGui::MenuItem("Save")) {
						mCurrentScene->Save();
						Debug::GetEngineLogger()->info("Save Current Scene");
					}
					if (ImGui::MenuItem("Empty GameObject")) {
						mCurrentScene->AddGameObject(shared_ptr<GameObject>(new GameObject()));
						Debug::GetEngineLogger()->info("Add Empty GameObject");
					}
					ImGui::EndMenu();
				}
				ImGui::EndMainMenuBar();
			} },
		"Editor"));
	RegisterGuiWindow(Menu);

	auto DockSpace = shared_ptr<GuiWindow>(new GuiWindow([]()
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
		"DockSpace"));
	RegisterGuiWindow(DockSpace);

	auto Hierarchy = shared_ptr<GuiWindow>(new GuiWindow([this]()
		{
			static bool hierarchy = true;
			if (hierarchy)
			{
				ImGui::Begin("Hierarchy", &hierarchy);
				if (mCurrentScene != nullptr)
				{
					if (ImGui::CollapsingHeader("currentScene"))
					{
						for (auto &i : mCurrentScene->gameobjects)
						{
							if (ImGui::Button(i->name.c_str()))
							{
								selectedObj = i;
							}
						}
					}
				}
				// Right-click on blank space
				if (ImGui::BeginPopupContextWindow(0, 1, false))
				{
					if (ImGui::MenuItem("Create Empty GameObject"))
					{
						mCurrentScene->AddGameObject(shared_ptr<GameObject>(new GameObject()));
						Debug::GetEngineLogger()->info("Add Empty GameObject");
					}
					ImGui::EndPopup();
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
				if (selectedObj != nullptr)
				{
					//show Components
					for (auto i : selectedObj->GetComponents())
					{
						if (ImGui::CollapsingHeader(i->GetName().c_str()))
						{
							i->GuiDisPlay();
						}
					}
					static bool listOpen = false;

					//add component button
					if (listOpen||ImGui::Button("Add Component", ImVec2(160, 30)))
					{
						listOpen = true;
						auto start = ReflectionManager::instance().GetMemberStartByTag(ReflectionTag::Component);
						int count= ReflectionManager::instance().GetMemberCountByTag(ReflectionTag::Component);
						for (int k = 0; k != count; k++, start++)
						{
							if (ImGui::Button(start->second.c_str(), ImVec2(140, 20)))
							{
								selectedObj->AddComponent((Component*)ReflectionManager::instance().CreateClassByName(start->second));
								listOpen = false;
							}
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
				{
					ImGui::BulletText(s.c_str());
				}

				ImGui::End();
			} },
		"Console"));
	RegisterGuiWindow(Console);

	auto SceneView = shared_ptr<GuiWindow>(new GuiWindow([this]()
		{
			ImGui::Begin("Scene");
			{
				static glm::vec2 lastPos = Input::MousePos();
				static int m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
				static int mode = ImGuizmo::WORLD;
				static const float identityMatrix[16] =
				{
					1.f, 0.f, 0.f, 0.f,
					0.f, 1.f, 0.f, 0.f,
					0.f, 0.f, 1.f, 0.f,
					0.f, 0.f, 0.f, 1.f
				};
				bool snap = Input::GetKeyDown(GLFW_KEY_LEFT_CONTROL);
				
				if(ImGui::Button("T"))
					m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
				ImGui::SameLine();
				if (ImGui::Button("R"))
					m_GizmoType = ImGuizmo::OPERATION::ROTATE;			
				ImGui::SameLine();
				if (ImGui::Button("S"))
					m_GizmoType = ImGuizmo::OPERATION::SCALE;	

				ImGui::SameLine();
				if (ImGui::Button("W"))
					mode = ImGuizmo::MODE::WORLD;				
				ImGui::SameLine();
				if (ImGui::Button("L"))
					mode = ImGuizmo::MODE::LOCAL;

				//设置多视口参数
				auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
				auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
				auto viewportOffset = ImGui::GetWindowPos();
				glm::vec2 m_ViewportBounds0 = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
				glm::vec2 m_ViewportBounds1 = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };
				ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
				
				//渲染场景至编辑器
				auto mainFB = Application::instance().mWindows->GetMianFrameBuffer(); 
				auto shadowMap=TLEngineCG::shadowMap; 
				ImGui::Image((ImTextureID)mainFB->GetColorBuffer()->texture, viewportPanelSize, ImVec2(0, 1), ImVec2(1, 0));
				mainFB->Resize(viewportPanelSize.x, viewportPanelSize.y);
				shadowMap->Resize(Application::instance().mWindows->GetWidth(), Application::instance().mWindows->GetHeight());
				//渲染gizmos
				if (selectedObj)
				{
					ImGuizmo::SetOrthographic(false);
					ImGuizmo::SetDrawlist();

					//设置gizmos大小
					ImGuizmo::SetRect(m_ViewportBounds0.x, m_ViewportBounds0.y, viewportPanelSize.x, viewportPanelSize.y);

					const glm::mat4& cameraProjection = GetEditorCamera()->GetProjMatrix();
					glm::mat4 cameraView = GetEditorCamera()->GetViewMatrix();
					glm::mat4 model = selectedObj->transform->GetModelMatrix();

					float snapValue = 0.5f;
					float snapValues[3] = { snapValue, snapValue, snapValue };

					ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
						(ImGuizmo::OPERATION)m_GizmoType, (ImGuizmo::MODE)mode, glm::value_ptr(model),
						nullptr, snap ? snapValues : nullptr);
					//ImGuizmo::DrawGrid(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), identityMatrix, 100.f);
				
					if (ImGuizmo::IsUsing())
					{
						selectedObj->transform->Decompose(model);
					}
				}

				//输入处理
				if (Input::GetKeyDown(GLFW_KEY_W))
					m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
				else if (Input::GetKeyDown(GLFW_KEY_E))
					m_GizmoType = ImGuizmo::OPERATION::ROTATE;
				else if (Input::GetKeyDown(GLFW_KEY_R))
					m_GizmoType = ImGuizmo::OPERATION::SCALE;
				else if (Input::GetKeyDown(GLFW_KEY_T))
					m_GizmoType = ImGuizmo::OPERATION::SCALEU;
				else if (Input::GetKeyDown(GLFW_KEY_Y))
					m_GizmoType = ImGuizmo::OPERATION::UNIVERSAL;
				if (Input::GetMouseButtonDown(GLFW_MOUSE_BUTTON_2) || Input::GetMouseButtonDown(GLFW_MOUSE_BUTTON_3))
				{
					lastPos = Input::MousePos();
				}
				
				if (Input::GetMouseButton(GLFW_MOUSE_BUTTON_2))
				{
					glm::vec2 dir = Input::MousePos() - lastPos;
					editorCamera->transform->rotation.x -= dir.x / 10;
					editorCamera->transform->rotation.z += dir.y / 10;
					lastPos = Input::MousePos();
				}
				
				if (Input::GetMouseButton(GLFW_MOUSE_BUTTON_3))
				{
					glm::vec2 dir = Input::MousePos() - lastPos;
					editorCamera->transform->Translate(editorCamera->transform->GetRight(), -dir.x / 60);
					editorCamera->transform->Translate(editorCamera->transform->GetUp(), dir.y / 60);
					lastPos = Input::MousePos();
				}

				//ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 2));
				//ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
				//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
				//auto& colors = ImGui::GetStyle().Colors;
				//const auto& buttonHovered = colors[ImGuiCol_ButtonHovered];
				//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(buttonHovered.x, buttonHovered.y, buttonHovered.z, 0.5f));
				//const auto& buttonActive = colors[ImGuiCol_ButtonActive];
				//ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(buttonActive.x, buttonActive.y, buttonActive.z, 0.5f));

				//ImGui::Begin("##toolbar", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

				//bool toolbarEnabled = (bool)m_ActiveScene;

				//ImVec4 tintColor = ImVec4(1, 1, 1, 1);
				//if (!toolbarEnabled)
				//	tintColor.w = 0.5f;

				//float size = ImGui::GetWindowHeight() - 4.0f;
				//{
				//	Ref<Texture2D> icon = (m_SceneState == SceneState::Edit || m_SceneState == SceneState::Simulate) ? m_IconPlay : m_IconStop;
				//	ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) - (size * 0.5f));
				//	if (ImGui::ImageButton((ImTextureID)icon->GetRendererID(), ImVec2(size, size), ImVec2(0, 0), ImVec2(1, 1), 0, ImVec4(0.0f, 0.0f, 0.0f, 0.0f), tintColor) && toolbarEnabled)
				//	{
				//		if (m_SceneState == SceneState::Edit || m_SceneState == SceneState::Simulate)
				//			OnScenePlay();
				//		else if (m_SceneState == SceneState::Play)
				//			OnSceneStop();
				//	}
				//}
				//ImGui::SameLine();
				//{
				//	Ref<Texture2D> icon = (m_SceneState == SceneState::Edit || m_SceneState == SceneState::Play) ? m_IconSimulate : m_IconStop;		//ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) - (size * 0.5f));
				//	if (ImGui::ImageButton((ImTextureID)icon->GetRendererID(), ImVec2(size, size), ImVec2(0, 0), ImVec2(1, 1), 0, ImVec4(0.0f, 0.0f, 0.0f, 0.0f), tintColor) && toolbarEnabled)
				//	{
				//		if (m_SceneState == SceneState::Edit || m_SceneState == SceneState::Play)
				//			OnSceneSimulate();
				//		else if (m_SceneState == SceneState::Simulate)
				//			OnSceneStop();
				//	}
				//}
				//ImGui::PopStyleVar(2);
				//ImGui::PopStyleColor(3);
				//ImGui::End();
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
	RenderEnd();
}

void EditorLayer::SetCurrentScene(Scene* s)
{
	mCurrentScene = shared_ptr<Scene>(s);
}

Camera* EditorLayer::GetEditorCamera()
{
	return editorCamera->GetComponent<Camera>();
}

bool EditorLayer::OnMouseMovedEvent(MouseMovedEvent& e)
{
	return true;
}

bool EditorLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseWheelH += e.GetXOffset();
	io.MouseWheel += e.GetYOffset();

	editorCamera->transform->Translate(editorCamera->transform->GetFront(), e.GetYOffset());

	return true;
}
