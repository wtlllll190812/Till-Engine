#pragma once
#include "System.h"
#include <queue>
#include "UniformBuffer.h"
#include <memory>

class Component;
class Renderer;
class Camera;
class RenderSystem : public System, public Singleton<RenderSystem>
{
public:
	RenderSystem();
	~RenderSystem();

	/// <summary>
	/// 渲染队列
	/// </summary>
	static std::priority_queue<Renderer*, std::vector<Renderer*>> renderQueue;

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
	virtual void RegisterComponent(Component*) override;

	/// <summary>
	/// 移除组件
	/// </summary>
	virtual void RemoveComponent(Component*) override;

	/// <summary>
	/// 清空
	/// </summary>
	void Clear();

	inline void SetCamera(std::shared_ptr<Camera> camera) { currentCamera = camera; };

private:
	UniformBuffer maticesUniformBuffer;
	UniformBuffer lightUniformBuffer;
	std::shared_ptr<Camera> currentCamera;
};