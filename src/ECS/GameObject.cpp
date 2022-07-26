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
	if (m_node == nullptr)
		m_node = new TiXmlElement(name);

	m_node->SetAttribute("name", name);
	m_node->SetAttribute("guid", std::to_string(guid));
	for (auto i : components)
	{
		m_node->LinkEndChild(i->Serialize());
	}
	return m_node;
}

void GameObject::DeSerialize(TiXmlElement* node)
{
	m_node = node;
	guid = std::stoi(node->Attribute("guid"));
	name = node->Attribute("name");
	
	for (auto n = node->FirstChildElement(); n != 0; n = n->NextSiblingElement())
	{
		Debug::GetEngineLogger()->info("Scene Load {0}", n->Value());
		if (strcmp(n->Value(), "Transform") != 0)
		{
			auto comp = (Component*)ReflectionManager::instance().CreateClassByName(n->Value());
			comp->DeSerialize(n);
			if (strcmp(n->Value(), "Camera") == 0)
			{
				owner->mainCamera = (Camera*)comp;
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

void GameObject::UpdateNode()
{
	if (m_node)
	{
		m_node->SetAttribute("name", name);
		m_node->SetAttribute("guid", std::to_string(guid));
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