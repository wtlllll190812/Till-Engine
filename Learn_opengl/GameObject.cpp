#include"GameObject.h"

GameObject::GameObject()
{
	name = "GameObject";
}

GameObject::~GameObject()
{
}

void GameObject::AddComponent(Component* comp)
{
	components.push_back(comp);
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
	TLxml* xml=new TLxml(name);
	for(auto i:components)
	{
		xml->AddChild(i->Serialize()->pRoot);
	}
	return xml;
}
