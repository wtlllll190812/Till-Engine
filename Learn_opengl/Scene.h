#pragma once
#include "TLxml.h"
#include <string>
#include <vector>

class Scene
{
public:
	Scene(std::string);
	~Scene();

private:
	std::string path;
	TLxml xml;
};

