#include "WindowsWindow.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
#include "ApplicationEvent.h"


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
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//配置opengl版本
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//配置opengl版本
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//使用核心模式,使用旧版函数时会出错
		//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//禁止调整窗口大小
		
        glfwSetErrorCallback([](int error_code, const char* description)
            {
                Debug::GetEngineLogger()->error(description);
            });
		//设置窗口
        Debug::GetEngineLogger()->info("GlfwWindows Init");
        glfwInitialized = true;
    }
    mWindow = glfwCreateWindow((int)props.Width,(int)props.Height,mData.Title.c_str(),nullptr,nullptr);


    glfwMakeContextCurrent(mWindow);
    glfwSetWindowUserPointer(mWindow,&mData);
    SetVSync(true);
    glViewport(0, 0, mData.Width, mData.Height);//前两个参数控制左下角的位置
    ////启用深度测试
    glEnable(GL_DEPTH_TEST);

    //Set FLFW Callback
    glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int heigth) 
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = heigth;

            WindowResizeEvent event(width, heigth);
            data.EventCallback(event);
        });

    glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.EventCallback(event);
        }); 

    glfwSetKeyCallback(mWindow, [](GLFWwindow* window,int key,int scancode,int action,int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key,0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
            }
        });

    glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

    glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });   

    glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double x, double y)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)x, (float)y);
            data.EventCallback(event);
        });
}

void WindowsWindow::ShutDown()
{
    glfwDestroyWindow(mWindow);
}
