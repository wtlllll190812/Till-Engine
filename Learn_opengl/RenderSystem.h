#pragma once
#include<queue>
#include<vector>
#include"System.h"



class Component;
class Renderer;
class RenderSystem:public System,public Singleton<RenderSystem>
{
public:
	RenderSystem();
	~RenderSystem();
	static std::priority_queue <Renderer*, std::vector<Renderer*>> renderQueue;

	// Í¨¹ý System ¼Ì³Ð
	virtual void Update() override;

	virtual void FixedUpdate() override;

	virtual void RegisterComponent(Component*) override;

	virtual void RemoveComponent(Component*) override;

	void Clear();
};