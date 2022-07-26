#pragma once
#include "System.h"
#include <queue>
#include "UniformBuffer.h"
#include <memory>

class Component;
class Renderer;
class Camera;
/// <summary>
/// 渲染系统
/// </summary>
class RenderSystem : public System, public Singleton<RenderSystem>
{
public:
	/// <summary>
	/// 当前摄像机
	/// </summary>
	std::shared_ptr<Camera> currentCamera;

	/// <summary>
	/// 渲染队列
	/// </summary>
	static std::priority_queue<Renderer*, std::vector<Renderer*>> renderQueue;

public:
	RenderSystem();
	~RenderSystem();

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

	/// <summary>
	/// 设置当前摄像机
	/// </summary>
	inline void SetCamera(std::shared_ptr<Camera> mainCamera) { currentCamera = mainCamera; };
private:
	/// <summary>
	/// 矩阵UBO
	/// </summary>
	UniformBuffer maticesUB;
	
	/// <summary>
	/// 光照UBO
	/// </summary>
	UniformBuffer mainLightUB;

private:
	/// <summary>
	/// 配置渲染数据
	/// </summary>
	void SetData();

	/// <summary>
	/// 渲染阴影
	/// </summary>
	void RenderShadow(std::priority_queue <Renderer*, std::vector<Renderer*>>);
};