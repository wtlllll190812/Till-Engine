#pragma once
#include <vector>
#include "TLxml.h"
#include"Reflection.h"
#include"Transform.h"


class GameObject
{
public:
	Transform* transform;
	std::string name;//物体名称
	int guid;//物体标识

	GameObject();
	GameObject(TiXmlNode*);
	~GameObject();

	/// <summary>
	/// 物体刷新
	/// </summary>
	void Update();

	/// <summary>
	/// 序列化
	/// </summary>
	TLxml* Serialize();

	/// <summary>
	/// 获取hash值
	/// </summary>
	int GetHash();

	/// <summary>
	/// 添加组件
	/// </summary>
	/// <param name=""></param>
	void AddComponent(Component*);

	/// <summary>
	/// 获取组件
	/// </summary>
	/// <typeparam name="T">组件类型</typeparam>
	/// <returns>组件对象</returns>
	template <class T>
	T* GetComponent()
	{
		for (auto it = components.begin(); it != components.end(); it++)
		{
			auto com = dynamic_cast<T*>(*it);
			if (com)
			{
				return com;
			}
		}
		std::cout << "Component is not exist" << std::endl;
		return nullptr;
	}

	/// <summary>
	/// 移除组件
	/// </summary>
	/// <typeparam name="T">组件类型</typeparam>
	template <class T>
	void RemoveComponent()
	{
		for (auto it = components.begin(); it != components.end(); it++)
		{
			if (dynamic_cast<T*>(*it))
			{
				(*it)->OnRemove();
				delete (*it);
			}
		}
		std::cout << "Component is not exist" << std::endl;
		return nullptr;
	}

	bool operator==(const GameObject& g)const {
		return g.guid == this->guid;
	}
private:
	std::vector<Component*> components;
};

