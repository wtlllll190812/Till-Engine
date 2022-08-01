#pragma once
#include <glm/glm.hpp>

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
	static void Init();
	static glm::vec2 MousePos();
private:
	static int keyBuf[512];
	static int mouseBuf[8];
};
