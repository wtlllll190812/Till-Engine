#pragma once
#include<vector>
#include<string>
#include<iostream>
#include "Component.h"

class GameObject
{
public:
	GameObject();
	~GameObject();
	void AddComponent(Component*);
    //template <class T>void RemoveComponent(std::string& name)
    
    template <class T>T* GetComponent()
    {
        for (auto it = components.begin(); it != components.end(); it++)
        {
            auto com dynamic_cast<T*>(*it);
            if (com)
            {
                return com;
            }
        }
        Debug::Instance().Log("Component is not exist");
        return nullptr;
    }
	
    void Update();
private:
    std::vector<Component*> components;
};