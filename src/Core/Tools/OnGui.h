#pragma once
#include <string>
#include "glm/glm.hpp"
#include "imgui.h"
#include <imgui/imgui_internal.h>

class IGuiDisplay
{
public:
	virtual void GuiDisPlay()=0;
	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f);
};

