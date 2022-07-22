#include"GameObject.h"
#include "Scene.h"
#include "Camera.h"
#include "Transform.h"
#include "Debug.h"
#include "Reflection.h"

REFLECTION(GameObject, GameObject);

GameObject::GameObject()
{
	name = "GameObject";
	guid = GetHash();
	transform = new Transform();
	components.push_back(transform);
	transform->gameobject = this;
	transform->Awake();
}

GameObject::GameObject(TiXmlElement* node, Scene* s)
{
	owner = s;
	DeSerialize(node);
}

GameObject::~GameObject()
{
}

void GameObject::AddComponent(Component* comp)
{
	components.push_back(comp);
	comp->gameobject = this;
	comp->Awake();
	if (transform == nullptr)transform = dynamic_cast<Transform*>(comp);
}

TiXmlElement* GameObject::Serialize(std::string)
{
	TiXmlElement* xml = new TiXmlElement(name);
	for (auto i : components)
	{
		xml->SetAttribute("name", name);
		xml->SetAttribute("guid", std::to_string(guid));
		xml->LinkEndChild(i->Serialize());
	}
	return xml;
}

void GameObject::DeSerialize(TiXmlElement* node)
{
	guid = std::stoi(node->Attribute("guid"));
	name = node->Attribute("name");
	
	for (auto n = node->FirstChildElement(); n != 0; n = n->NextSiblingElement())
	{
		Debug::GetEngineLogger()->info("Scene Load {0}", n->Value());
		if (strcmp(n->Value(), "Transform") != 0)
		{
			auto comp = (Component*)ReflectionManager::instance().getClassByName(n->Value());
			comp->DeSerialize(n);
			if (strcmp(n->Value(), "Camera") == 0)
			{
				owner->camera = (Camera*)comp;
			}
			AddComponent(comp);
		}
		else
		{
			transform = new Transform();
			transform->DeSerialize(n);
			AddComponent(transform);
		}
	}
}

void GameObject::Update()
{
	for (auto i = components.begin(); i != components.end(); ++i)
	{
		(*i)->OnUpdate();
	}
}

int GameObject::GetHash()
{
	std::hash<GameObject*> h;
	return (h(this));
}