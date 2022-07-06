#include "Input.h"
#include "WindowsWindow.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Application.h"

GLFWwindow* window;

bool Input::GetKeyDown(const int key)
{
	if(window==nullptr)
		window = static_cast<GLFWwindow*>(Application::instance().mWindows->GetWindow());
	auto state = glfwGetKey(window, static_cast<int32_t>(key));
	return state == GLFW_PRESS;
}

bool Input::GetKeyUp(const int key)
{
	if (window == nullptr)
		window = static_cast<GLFWwindow*>(Application::instance().mWindows->GetWindow());
	auto state = glfwGetKey(window, static_cast<int32_t>(key));
	return state == GLFW_RELEASE;
}

bool Input::GetKey(const int key)
{
	if (window == nullptr)
		window = static_cast<GLFWwindow*>(Application::instance().mWindows->GetWindow());	
	auto state = glfwGetKey(window, static_cast<int32_t>(key));
	return state == GLFW_REPEAT;
}

bool Input::MouseButtonDown(const int key)
{
	if (window == nullptr)
		window = static_cast<GLFWwindow*>(Application::instance().mWindows->GetWindow());
	auto state = glfwGetMouseButton(window, static_cast<int32_t>(key));
	return state == GLFW_PRESS;
}

bool Input::MouseButtonUp(const int key)
{
	if (window == nullptr)
		window = static_cast<GLFWwindow*>(Application::instance().mWindows->GetWindow());	
	auto state = glfwGetMouseButton(window, static_cast<int32_t>(key));
	return state == GLFW_RELEASE;
}

bool Input::MouseButton(const int key)
{
	if (window == nullptr)
		window = static_cast<GLFWwindow*>(Application::instance().mWindows->GetWindow());	
	auto state = glfwGetMouseButton(window, static_cast<int32_t>(key));
	return state == GLFW_REPEAT;
}

glm::vec2 Input::MousePos()
{
	if (window == nullptr)
		window = static_cast<GLFWwindow*>(Application::instance().mWindows->GetWindow());
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	return { (float)xpos, (float)ypos };
}
