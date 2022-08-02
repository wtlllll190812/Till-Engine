#include "WindowsWindow.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <SOIL2/SOIL2.h>

#include "KeyEvent.h"
#include "MouseEvent.h"
#include "ApplicationEvent.h"

#include "RenderSystem.h"
#include "Debug.h"
#include "TLCore.h"

//是否已经初始化
static bool glfwInitialized = false;

Window* Window::Create(const WindowProps& props)
{
	return new WindowsWindow(props);
}

WindowsWindow::WindowsWindow(const WindowProps& props)
{
	WindowInit(props);
}

WindowsWindow::~WindowsWindow()
{
	ShutDown();
}

void WindowsWindow::DrawFunc()
{
	glfwPollEvents();
	glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	//glFrontFace(GL_CW); //设置三角形点顺序

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//清空所有缓存区
	for(int i=0;i<framebuffer.size();++i)
	{
		SetFrameBuffer(i);
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	//调用渲染系统
	RenderSystem::instance().Update();
	SetFrameBuffer(-1);
}

void WindowsWindow::OnRenderEnd()
{
	glfwSwapBuffers(mWindow);
}

void WindowsWindow::SetFrameBuffer(int index)
{
	if (index == -1)
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	else
	{
		currentBuffer = framebuffer[index];
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer[index]->GetFBO());
	}
}

void WindowsWindow::SetFrameBuffer(FrameBuffer* buffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, buffer->GetFBO());
}

void WindowsWindow::SetDepthTest(bool isOn)
{
	isOn ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

void WindowsWindow::SetDepthFunc(DepthTestFunc func)
{
	switch (func)
	{
	case DepthTestFunc::always:
		glDepthFunc(GL_ALWAYS);
		break;
	case DepthTestFunc::never:
		glDepthFunc(GL_NEVER);
		break;
	case DepthTestFunc::less:
		glDepthFunc(GL_LESS);
		break;
	case DepthTestFunc::greater:
		glDepthFunc(GL_GREATER);
		break;
	case DepthTestFunc::equal:
		glDepthFunc(GL_EQUAL);
		break;
	case DepthTestFunc::lEqual:
		glDepthFunc(GL_LEQUAL);
		break;
	case DepthTestFunc::gEqual:
		glDepthFunc(GL_GREATER);
		break;
	case DepthTestFunc::notEqual:
		glDepthFunc(GL_NOTEQUAL);
		break;
	default:
		break;
	}
}

void WindowsWindow::SetDepthWrite(bool isOn)
{
	isOn ? glDepthMask(GL_TRUE):glDepthMask(GL_FALSE);
}

void WindowsWindow::SetCullFace(CullMode mode)
{
	switch (mode)
	{
	case CullMode::front:
		glCullFace(GL_FRONT);
		break;
	case CullMode::back:
		glCullFace(GL_BACK);
		break;
	case CullMode::both:
		glCullFace(GL_FRONT_AND_BACK);
		break;
	default:
		Debug::GetEngineLogger()->error("Cull mode not exist");
		break;
	}
}

void WindowsWindow::SetSRGB(bool isOn)
{
	isOn ? glEnable(GL_FRAMEBUFFER_SRGB) : glDisable(GL_FRAMEBUFFER_SRGB);
}

float WindowsWindow::GetTime()
{
	return glfwGetTime();
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

void WindowsWindow::WindowInit(const WindowProps& props)
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
		//glfwWindowHint(GLFW_SAMPLES, 4);
		/*glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);*/

		glfwSetErrorCallback([](int error_code, const char* description)
			{
				Debug::GetEngineLogger()->error(description);
			});
		//设置窗口
		Debug::GetEngineLogger()->info("GlfwWindows Init");
		glfwInitialized = true;
	}
	mWindow = glfwCreateWindow((int)props.Width, (int)props.Height, mData.Title.c_str(), nullptr, nullptr);
	int w, h;
	unsigned char* image = SOIL_load_image(IMAGE_PATH"engine/Till_Engine.png", &w, &h, 0, SOIL_LOAD_RGB);
	GLFWimage glfwimage{ w,h,image };
	glfwSetWindowIcon(mWindow, 1, &glfwimage);
	SOIL_free_image_data(image);

	glfwMakeContextCurrent(mWindow);
	glfwSetWindowUserPointer(mWindow, &mData);
	SetVSync(true);
	glViewport(0, 0, mData.Width, mData.Height);//前两个参数控制左下角的位置
	////启用深度测试
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_MULTISAMPLE);

	////初始化GLEW,用于管理opengl的函数指针
	glewExperimental = GL_TRUE;
	//初始化失败时
	if (glewInit() != GLEW_OK)
	{
		Debug::GetEngineLogger()->error("Failed to initialize GLEW");
		return;
	}
	SetCallback();
	mainBuffer=AddFrameBuffer(BufferType::Both);
}

void WindowsWindow::ShutDown()
{
	for (auto i : framebuffer)
		delete i;
	glfwTerminate();
}

void WindowsWindow::SetCallback()
{
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

	glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
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