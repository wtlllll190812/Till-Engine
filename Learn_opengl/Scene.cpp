#include "Scene.h"

Scene::Scene(std::string p):path(p),xml(TLxml(p,"scene"))
{
	for (auto node = xml.pRoot->FirstChild(); node != 0; node = node->NextSibling())
	{
		auto element = node->ToElement();
		gameobjects.push_back(new GameObject(element));
	}
}

Scene::~Scene()
{
}

void Scene::Save()
{
}
