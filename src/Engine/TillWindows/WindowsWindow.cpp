#include "WindowsWindow.h"

static bool glfwInitialized = false;

TillWindow* TillWindow::Create(const WindowProps& props)
{
    return new WindowsWindow(props);
}

WindowsWindow::WindowsWindow(const WindowProps& props)
{
    Init(props);
}

WindowsWindow::~WindowsWindow()
{
    ShutDown();
}

void WindowsWindow::OnUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(mWindow);
}

void WindowsWindow::SetVSync(bool enabled)
{
    if (enabled)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    mData.VSync = enabled;
}

bool WindowsWindow::IsVSync() const
{
    return mData.VSync;
}

void WindowsWindow::Init(const WindowProps& props)
{
	Debug::GetEngineLogger()->info("GlfwWindows Init");
    mData.Title = props.Title;
    mData.Width = props.Width;
    mData.Height = props.Height;
   
    if (!glfwInitialized)
    {
        int success = glfwInit();
		glfwInit();//初始化GLFW
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//配置opengl版本
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//配置opengl版本
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//使用核心模式,使用旧版函数时会出错
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//禁止调整窗口大小
		
		//初始化glad
		/*if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return ;
		}*/

		//设置窗口
        if(success!=0)
        Debug::GetEngineLogger()->info("GlfwWindows Init");
        glfwInitialized = true;
    }
    mWindow = glfwCreateWindow((int)props.Width,(int)props.Height,mData.Title.c_str(),nullptr,nullptr);
    ////初始化GLEW,用于管理opengl的函数指针
    glewExperimental = GL_TRUE;
    //初始化失败时
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return;
    }
    
    glfwMakeContextCurrent(mWindow);
    glfwSetWindowUserPointer(mWindow,&mData);
    SetVSync(true);
    glViewport(0, 0, mData.Width, mData.Height);//前两个参数控制左下角的位置
    //启用深度测试
    glEnable(GL_DEPTH_TEST);

    //Set FLFW Callback
    glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int heigth) 
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        });
}

void WindowsWindow::ShutDown()
{
    glfwDestroyWindow(mWindow);
}
