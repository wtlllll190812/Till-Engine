#include"GameObject.h"
#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include "Scene.h"



#include "Camera.h"

REFLECTION(GameObject);

GameObject::GameObject()
{
	name = "GameObject";
	guid = GetHash();
}

GameObject::GameObject(TiXmlNode* xml,Scene* s)
{
	owner = s;
	auto element = xml->ToElement();
	guid = std::stoi(element->Attribute("guid"));
	name = element->Attribute("name");
	for (auto node = element->FirstChild(); node != 0; node = node->NextSibling())
	{
		auto element = node->ToElement();
		if (strcmp(element->Value(), "Transform") != 0)
		{
			auto comp = (Component*)Reflection::instance().getClassByName(element->Value());
			comp->Instantiate(element);
			if (strcmp(element->Value(), "Camera") == 0)
			{
				s->camera = (Camera*)comp;
				std::cout << s->camera->guid << std::endl;
			}
			AddComponent(comp);
		}
		else
		{
			transform = new Transform();
			transform->Instantiate(element);
			AddComponent(transform);
		}
		/*switch (element->Value())
		{
		default:
			break;
		}*/
	}
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

void GameObject::Update()
{
	for (auto i = components.begin(); i != components.end(); i++)
	{
		(*i)->OnUpdate();
	}
}

TLxml* GameObject::Serialize()
{
	TLxml* xml = new TLxml(name);
	for (auto i : components)
	{
		xml->pRoot->SetAttribute("name", name);
		xml->pRoot->SetAttribute("guid", std::to_string(guid));
		xml->AddChild(i->Serialize()->pRoot);
	}
	return xml;
}

int GameObject::GetHash()
{
	std::hash<GameObject*> h;
	return (h(this));
}