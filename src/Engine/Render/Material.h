#pragma once
#include "Mesh.h"
#include "TLEngineCG.h"
#include <memory>

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
	void (*RenderCallback)(GameObject*, Shader*, Material*);

	Material(const char*, const char*);
	Material();
	~Material();

	void SetRenderCallback(void (*f)(GameObject*, Shader*, Material*));
	void Render(GameObject*, std::shared_ptr<Mesh>);
};
