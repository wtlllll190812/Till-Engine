#include"Screen.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include"GuiWindows.h"
#include"Debug.h"

Screen::Screen(int w, int h) :width(w), heigth(h)
{
	Debug::GetEngineLogger()->info("Screen Init");
	Init();
	GuiInit();
	Debug::GetEngineLogger()->info("Screen Inited");
}

Screen::Screen() : width(800), heigth(600)
{
	Debug::GetEngineLogger()->info("Screen Init");
	Init();
	GuiInit();
	Debug::GetEngineLogger()->info("Screen Inited");
}

Screen::~Screen()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}

void Screen::Display()
{
	glfwPollEvents();

	//清空屏幕以及缓存区
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glfwGetFramebufferSize(Screen::instance().window, &width, &heigth);
	glViewport(0, 0, width, heigth);
}

bool Screen::isClosed()
{
	return glfwWindowShouldClose(window);
}

void Screen::GuiInit()
{
	// 初始化imgui上下文
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// 设置imgui模式
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// 配置ImGui
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 100");
}

void Screen::GuiRender()
{
	// 开始渲染imgui
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	for (std::shared_ptr<GuiWindows> i : uiWindows)
	{
		i->Render();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Screen::RegisterGuiWindows(std::shared_ptr<GuiWindows> guiwindows)
{
	uiWindows.push_back(guiwindows);
}

void Screen::Init()
{
	glfwInit();//初始化GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//配置opengl版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//配置opengl版本
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//使用核心模式,使用旧版函数时会出错
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//禁止调整窗口大小

	window = glfwCreateWindow(width, heigth, "LearnOpenGL", nullptr, nullptr);//创建窗口并设置窗口大小

	//创建失败时
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);//设定为当前窗口
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	////初始化GLEW,用于管理opengl的函数指针
	glewExperimental = GL_TRUE;
	//初始化失败时
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return;
	}
	//初始化glad
	/*if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return ;
	}*/

	//设置窗口
	glViewport(0, 0, width, heigth);//前两个参数控制左下角的位置
	//启用深度测试
	glEnable(GL_DEPTH_TEST);
}