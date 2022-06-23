#pragma once
#include "Shader.h"
#include "Mesh.h"
#include "TLEngineCG.h"

class Material
{
public:
	Shader* shader;
	int renderQueueIndex = (int)RendererQueue::Geometry;
	void (*RenderCallback)(Shader*, Material*);

	Material(const GLchar*, const GLchar*);
	~Material();

	void SetRenderCallback(void (*f)(Shader*, Material*));
	void Render(Mesh*);
};

