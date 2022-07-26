#pragma once
#include "TLSerialize.h"

class GameObject;
/// <summary>
/// 组件基类
/// </summary>
class Component:public Serializable
{
public:
	/// <summary>
	/// 所属物体
	/// </summary>
	GameObject* gameobject;
	
	/// <summary>
	/// 全局标识
	/// </summary>
	int guid;

public:
	Component() : gameobject(nullptr), guid(GetHash()) {}
	const virtual std::string GetName() const = 0;

	/// <summary>
	/// 刷新时
	/// </summary>
	virtual void OnUpdate(){};

	/// <summary>
	/// 添加时
	/// </summary>
	virtual void Awake(){};

	/// <summary>
	/// 移除时
	/// </summary>
	virtual void OnRemove(){};

	/// <summary>
	/// 显示到Gui
	/// </summary>
	virtual void GuiDisPlay(){};

	/// <summary>
	/// 获取组件
	/// </summary>
	/// <typeparam name="T">组件类型</typeparam>
	/// <returns>组件对象</returns>
	template <class T>
	T* GetComponent()
	{
		return gameobject->GetComponent<T>();
	}
	
	/// <summary>
	/// 获取哈希值
	/// </summary>
	int GetHash()
	{
		std::hash<Component *> h;
		return (h(this));
	}
};

#define COMPONENTNAME(name)                              \
	static std::string GetStaticName() { return #name; } \
	virtual const std::string GetName() const override { return #name; }