#pragma once
#include "Shader.h"
#include "Mesh.h"
#include "TLEngineCG.h"
#include<memory>

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
	void (*RenderCallback)(Shader*, Material*);

	Material(const GLchar*, const GLchar*);
	Material();
	~Material();

	void SetRenderCallback(void (*f)(Shader*, Material*));
	void Render(shared_ptr<Mesh>);
};
