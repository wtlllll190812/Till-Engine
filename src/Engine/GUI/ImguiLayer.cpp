#include "ImguiLayer.h"
#include "GuiWindow.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include "TLTime.h"
#include "Application.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "TLCore.h"

#include "Debug.h"
ImguiLayer::ImguiLayer()
	:Layer("ImguiLayer")
{
}

ImguiLayer::~ImguiLayer()
{
	OnDetach();
}

void ImguiLayer::OnAttack()
{
	ImGuiInit();
}

void ImguiLayer::OnDetach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImguiLayer::OnUpdate()
{
	RenderStart();

	//ImGui::ShowDemoWindow();
	for (std::shared_ptr<GuiWindow> i : uiWindows)
	{
		i->Render();
	}
	RenderEnd();
}

void ImguiLayer::OnEvent(EventBase& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(ImguiLayer::OnMouseButtonPressedEvent));
	dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(ImguiLayer::OnMouseButtonReleasedEvent));
	dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(ImguiLayer::OnMouseButtonReleasedEvent));
	dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(ImguiLayer::OnMouseMovedEvent));
	dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(ImguiLayer::OnMouseScrolledEvent));
	dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(ImguiLayer::OnKeyPressedEvent));
	dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(ImguiLayer::OnWindowResizeEvent));
}

void ImguiLayer::RegisterGuiWindow(std::shared_ptr<GuiWindow> guiwindow)
{
	uiWindows.push_back(guiwindow);
}

bool ImguiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[e.GetMouseButton()] = true;

	return false;
}

bool ImguiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[e.GetMouseButton()] = false;

	return false;
}

bool ImguiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2(e.GetX(), e.GetY());
	return false;
}

bool ImguiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseWheelH += e.GetXOffset();
	io.MouseWheel += e.GetYOffset();
	return false;
}

bool ImguiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.KeysDown[e.GetKeyCode()] = true;

	io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	return false;
}

bool ImguiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.KeysDown[e.GetKeyCode()] = false;

	return false;
}

bool ImguiLayer::OnKeyTypedEvent(KeyPressedEvent& e)
{
	//ImGuiIO& io = ImGui::GetIO();
	//if (c > 0 && c < 0x10000)
	//	io.AddInputCharacter((unsigned char)c);

	return false;
}

bool ImguiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
	io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
	glViewport(0, 0, e.GetWidth(), e.GetHeight());
	return false;
}

void ImguiLayer::RenderStart()
{
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(Application::instance().mWindows->GetWidth(), Application::instance().mWindows->GetHeight());

	float time = (float)glfwGetTime();
	io.DeltaTime = mTime > 0.0f ? (time - mTime) : (1.0f / 60.0f);
	mTime = time;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImguiLayer::RenderEnd()
{
	ImGui::Draw();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	ImGuiIO& io = ImGui::GetIO();

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}

void ImguiLayer::ImGuiInit()
{
	static bool isInited = false;
	if (!isInited)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls

		ImGuiStyle* style = &ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			// theme from https://github.com/ocornut/imgui/issues/707
			ImGuiStyle& style = ImGui::GetStyle();
			style.WindowPadding = ImVec2(15, 15);
			style.WindowRounding = 5.0f;
			style.FramePadding = ImVec2(5, 5);
			style.FrameRounding = 4.0f;
			style.ItemSpacing = ImVec2(12, 8);
			style.ItemInnerSpacing = ImVec2(8, 6);
			style.IndentSpacing = 25.0f;
			style.ScrollbarSize = 15.0f;
			style.ScrollbarRounding = 9.0f;
			style.GrabMinSize = 5.0f;
			style.GrabRounding = 3.0f;
			style.WindowBorderSize = 0.0f;
			style.TabBorderSize = 0.0f;

			style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
			style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
			style.Colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
			style.Colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
			style.Colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
			style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			style.Colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
			style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
			style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
			style.Colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
			style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
			style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
			style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
			style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
			style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
			style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
			style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
			style.Colors[ImGuiCol_CheckMark] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
			style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
			style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
			style.Colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
			style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
			style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
			style.Colors[ImGuiCol_Header] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
			style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
			style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
			style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];
			style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
			style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
			style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
			style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
			style.Colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
			style.Colors[ImGuiCol_TabHovered] = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);
			style.Colors[ImGuiCol_TabActive] = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
			style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
			style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
			style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
			style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
			style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
			style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
			style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
			style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
			style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
			style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
			style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
			style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
			style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
			style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
			style.GrabRounding = style.FrameRounding = 2.3f;
		}
		ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(Application::instance().mWindows->GetWindow()), true);
		ImGui_ImplOpenGL3_Init("#version 410");
		isInited = true;
		

		//my style
		/*style.Colors[ImGuiCol_Text] = ImVec4(0.9f, 0.94f, 1.0f, 1.0f); 
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.69f, 0.72f, 0.76f, 1.0f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.16f, 0.17f, 0.2f, 1.0f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.15f, 0.17f, 1.0f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.13f, 0.15f, 0.17f, 1.0f);

		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.13f, 0.15f, 0.17f, 1.0f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.13f, 0.15f, 0.17f, 1.0f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.17f, 0.2f, 1.0f);


		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.13f, 0.15f, 0.17f, 1.0f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.16f, 0.17f, 0.2f, 1.0f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.16f, 0.17f, 0.2f, 1.0f);*/

		/*style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);


		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);*/




		//style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		//style.Colors[ImGuiCol_ComboBg] = ImVec4(0.86f, 0.86f, 0.86f, 0.99f);
		//style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
		//style.Colors[ImGuiCol_CloseButton] = ImVec4(0.59f, 0.59f, 0.59f, 0.50f);
		//style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
		//style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
		// //style.Colors[ImGuiCol_Column] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
		//style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
		//style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	}
}
