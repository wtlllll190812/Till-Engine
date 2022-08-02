#include "Input.h"
#include "WindowsWindow.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Debug.h"

GLFWwindow *window;

int Input::keyBuf[512];
int Input::mouseBuf[8];

bool Input::GetKeyDown(const int key)
{
	if (keyBuf[key] == -1)
		keyBuf[key] = 0;
	return keyBuf[key] == 2;
}

void Input::Init(std::unique_ptr<Window>& mainWindow)
{
	memset(keyBuf, -1, sizeof(keyBuf));
	memset(mouseBuf, -1, sizeof(mouseBuf));
	window = static_cast<GLFWwindow*>(mainWindow->GetWindow());
	Debug::GetAppLogger()->info(" Input::Init");
}

void Input::Update()
{
	for (int i = 0; i < 512; i++)
	{
		if (keyBuf[i] >= 0)
		{
			auto state = glfwGetKey(window, static_cast<int32_t>(i));
			if (state == GLFW_PRESS)
			{
				if (keyBuf[i] == 0)
					keyBuf[i] = 2;
				else
					keyBuf[i] = 3;
			}
			else if (keyBuf[i] > 1)
				keyBuf[i] = 1;
			else
				keyBuf[i] = 0;
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (mouseBuf[i] >= 0)
		{
			auto state = glfwGetMouseButton(window, static_cast<int32_t>(i));
			if (state == GLFW_PRESS)
			{
				if (mouseBuf[i] == 0)
					mouseBuf[i] = 2;
				else
					mouseBuf[i] = 3;
			}
			else if (mouseBuf[i] > 1)
				mouseBuf[i] = 1;
			else
				mouseBuf[i] = 0;
		}
	}
}

bool Input::GetKeyUp(const int key)
{
	if (keyBuf[key] == -1)
		keyBuf[key] = 0;
	return keyBuf[key] == 1;
}

bool Input::GetKey(const int key)
{
	if (keyBuf[key] == -1)
		keyBuf[key] = 0;
	return keyBuf[key] == 3;
}

bool Input::GetMouseButtonDown(const int key)
{
	if (mouseBuf[key] == -1)
		mouseBuf[key] = 0;
	return mouseBuf[key] == 2;
}

bool Input::GetMouseButtonUp(const int key)
{
	if (mouseBuf[key] == -1)
		mouseBuf[key] = 0;
	return mouseBuf[key] == 1;
}

bool Input::GetMouseButton(const int key)
{
	if (mouseBuf[key] == -1)
		mouseBuf[key] = 0;
	return mouseBuf[key] == 3;
}

glm::vec2 Input::MousePos()
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	return {(float)xpos, (float)ypos};
}
