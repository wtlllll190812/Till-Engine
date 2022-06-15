#include "GameObject.h"


GameObject::GameObject()
{
}

GameObject::~GameObject()
{

}

void GameObject::AddComponent(Component* comp)
{
	components.push_back(comp);
	if(transform==nullptr)transform=dynamic_cast<Transform*>(comp);
}

void GameObject::Update()
{
	for (auto i = components.begin(); i != components.end(); i++)
	{
		(*i)->OnUpdate();
	}
}