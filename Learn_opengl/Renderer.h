#pragma once
#include "Component.h"
#include "Material.h"
#include "Mesh.h"

class GameObject;
class Renderer :public Component
{
public:
	/// <summary>
	/// 模型Mesh
	/// </summary>
	Mesh* mesh;

	/// <summary>
	/// 材质
	/// </summary>
	Material* material;

	Renderer(Mesh*, Material*, GameObject*);
	~Renderer();

	/// <summary>
	/// 进行渲染
	/// </summary>
	void Render();

	/// <summary>
	/// 被添加时
	/// </summary>
	void OnAdd() override;

	bool operator>(const Renderer& r)
	{
		return r.material->renderQueueIndex > material->renderQueueIndex;
	}
};

