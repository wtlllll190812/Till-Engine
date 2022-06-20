#pragma once 
#include<glm/glm.hpp>
#include<vector>


class Light;
class TLEngineCG
{
public:
	TLEngineCG();
	~TLEngineCG();

	static std::vector<Light*> lights;
};

std::vector<Light*> TLEngineCG::lights = std::vector<Light*>();

TLEngineCG::TLEngineCG()
{
}

TLEngineCG::~TLEngineCG()
{
}