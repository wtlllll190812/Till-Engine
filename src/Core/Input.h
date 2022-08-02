#pragma once
#include <glm/glm.hpp>
#include "Window.h"
#include <memory>

class Input
{
public:
	static bool GetKeyDown(const int key);
	static bool GetKeyUp(const int key);
	static bool GetKey(const int key);
	static bool GetMouseButtonDown(const int key);
	static bool GetMouseButtonUp(const int key);
	static bool GetMouseButton(const int key);
	static void Update();
	static void Init(std::unique_ptr<Window>& mainWindow);
	static glm::vec2 MousePos();
private:
	static int keyBuf[512];
	static int mouseBuf[8];
};
