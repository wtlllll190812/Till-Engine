#pragma once
#include "Mesh.h"
#include "TLEngineCG.h"
#include <memory>
#include <functional>

class GameObject;
class Shader;
class Material
{
public:
	Shader* shader;

	/// <summary>
	/// 渲染队列次序
	/// </summary>
	int renderQueueIndex = (int)RendererQueue::Geometry;

	/// <summary>
	/// 渲染时回调
	/// </summary>
	std::function<void(GameObject*, Shader*, Material*)> RenderCallback;

	Material(const char*, const char*);
	Material();
	~Material();

	void SetRenderCallback(std::function<void(GameObject*, Shader*, Material*)> f);
	void Render(GameObject*, std::shared_ptr<Mesh>);
};
