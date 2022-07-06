#pragma once
#include <glm/glm.hpp>

class Input
{
public:
	static bool GetKeyDown(const int key);
	static bool GetKeyUp(const int key);
	static bool GetKey(const int key);
	static bool MouseButtonDown(const int key);
	static bool MouseButtonUp(const int key);
	static bool MouseButton(const int key);
	static glm::vec2 MousePos();
};
