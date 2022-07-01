#pragma once
#include <queue>
#include <vector>
#include "System.h"

class Component;
class Renderer;
class RenderSystem : public System, public Singleton<RenderSystem>
{
public:
	RenderSystem();
	~RenderSystem();

	/// <summary>
	/// 渲染队列
	/// </summary>
	static std::priority_queue<Renderer *, std::vector<Renderer *>> renderQueue;

	/// <summary>
	/// 每帧刷新
	/// </summary>
	virtual void Update() override;

	/// <summary>
	/// 固定时间刷新
	/// </summary>
	virtual void FixedUpdate() override;

	/// <summary>
	/// 注册组件
	/// </summary>
	virtual void RegisterComponent(Component *) override;

	/// <summary>
	/// 移除组件
	/// </summary>
	virtual void RemoveComponent(Component *) override;

	/// <summary>
	/// 清空
	/// </summary>
	void Clear();
};