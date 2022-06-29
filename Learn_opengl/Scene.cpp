#include "Scene.h"
#include "TLEngineCG.h"
#include "Renderer.h"
#include <queue>
#include <vector>

Scene::Scene(std::string p) :path(p), xml(TLxml(p, "scene"))
{
	for (auto node = xml.pRoot->FirstChild(); node != 0; node = node->NextSibling())
	{
		auto element = node->ToElement();
		gameobjects.push_back(new GameObject(element, this));
	}
}

Scene::~Scene()
{
	/*for (auto i : gameobjects)
	{
		delete i;
	}*/
	Save();
}

void Scene::Save()
{
	/*for (auto i : gameobjects)
	{
		xml.AddChild(i->Serialize()->pRoot);
	}*/
	xml.Save();
}

GameObject* Scene::Find(std::string name)
{
	for (auto i : gameobjects)
	{
		if (i->name == name)
			return i;
	}
	return nullptr;
}