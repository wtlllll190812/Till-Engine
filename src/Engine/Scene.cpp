#include "Scene.h"
#include "TLEngineCG.h"
#include "Renderer.h"
#include <queue>
#include <vector>
#include "Debug.h"
#include "GameObject.h"

Scene::Scene(std::string p) :path(p), xml(TLxml(p, "scene"))
{
	Debug::GetEngineLogger()->info("Scene Loading");
	for (auto node = xml.pRoot->FirstChild(); node != 0; node = node->NextSibling())
	{
		auto element = node->ToElement();
		gameobjects.push_back(std::shared_ptr<GameObject>(new GameObject(element, this)));
	}
	Debug::GetEngineLogger()->info("Scene Loaded");
}

Scene::~Scene()
{
	Save();
}

void Scene::Save()
{
	xml.Save();
}

std::shared_ptr<GameObject> Scene::Find(std::string name)
{
	for (auto i : gameobjects)
	{
		if (i->name == name)
			return i;
	}
	return nullptr;
}