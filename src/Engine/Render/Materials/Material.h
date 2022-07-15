#pragma once
#include "TLEngineCG.h"
#include <memory>
#include <functional>

class GameObject;
class Shader;
class Mesh;
class Material
{
public:
	Shader* shader;

	/// <summary>
	/// 渲染队列次序
	/// </summary>
	int renderQueueIndex = (int)RendererQueue::Geometry;

public:
	Material();
	~Material();

	void Render(GameObject*, std::shared_ptr<Mesh>);
	virtual void OnRender(GameObject* gObj,std::shared_ptr<Mesh> mesh) = 0;
	virtual void BeforeRender(GameObject*, std::shared_ptr<Mesh> mesh) = 0;
private:
	bool inited;
};