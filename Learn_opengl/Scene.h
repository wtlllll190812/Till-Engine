#pragma once
#include "TLxml.h"
#include <string>
#include <vector>
#include "GameObject.h"

class Scene
{
public:
	Scene(std::string);
	~Scene();
	void Save();
private:
	std::string path;
	std::vector<GameObject*> gameobjects;
	TLxml xml;
};

