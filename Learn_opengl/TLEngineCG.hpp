#pragma once
#include<glm/glm.hpp>
#include<vector>
#include<queue>

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
	static std::priority_queue < Renderer*, vector<Renderer*>> renderQueue;
};
std::vector<Light*> TLEngineCG::lights = std::vector<Light*>();
std::priority_queue < Renderer*, std::vector<Renderer*>> TLEngineCG::renderQueue = std::priority_queue < Renderer*, std::vector<Renderer*>>();

TLEngineCG::TLEngineCG()
{
}

TLEngineCG::~TLEngineCG()
{
}