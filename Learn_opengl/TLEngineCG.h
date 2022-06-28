#pragma once
#include<glm/glm.hpp>
#include<vector>
#include<queue>
#include"Reflection.h"
enum class RendererQueue
{
	Background = 1000,
	Geometry = 2000,
	AlphaTest = 2450,
	Transparent = 3000,
	Overlay = 4000
};
class Light;
class Renderer;
class TLEngineCG
{
public:
	TLEngineCG();
	~TLEngineCG();

	static std::vector<Light*> lights;
};


