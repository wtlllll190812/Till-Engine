#include "Scene.h"
#include "TLEngineCG.h"
#include "Renderer.h"
#include <queue>
#include <vector>
#include "Debug.h"
#include "GameObject.h"

Scene::Scene(std::string p) :path(p), xml(TLSerializeFile(p, "scene"))
{
	Debug::GetEngineLogger()->info("Scene Loading");
	for (auto node = xml.GetRoot()->FirstChild(); node != nullptr; node = node->NextSiblingElement())
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
	Debug::GetEngineLogger()->info("Scene Saving");
	xml.Save();
	Debug::GetEngineLogger()->info("Scene Saved");
}

std::shared_ptr<GameObject> Scene::Find(std::string name)
{
	for (auto &i : gameobjects)
	{
		if (i->name == name)
			return i;
	}
	return nullptr;
}