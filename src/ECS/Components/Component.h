#pragma once
#include "TLSerialize.h"

class GameObject;
class Component:public Serializable
{
public:
	const virtual std::string GetName() const = 0;

	GameObject *gameobject;
	int guid;

	Component() : gameobject(nullptr), guid(GetHash()) {}

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