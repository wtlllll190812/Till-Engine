#include "GameObject.h"


GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	for (auto i = components.begin(); i != components.end(); i++)
	{
		delete *i;
	}
}

void GameObject::Update()
{
	for (auto i = components.begin(); i != components.end(); i++)
	{
		(*i)->OnUpdate();
	}
}