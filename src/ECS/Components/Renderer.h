#pragma once
#include "Component.h"
#include "Material.h"
#include "Mesh.h"

class GameObject;
class Renderer : public Component
{
public:
	COMPONENTNAME(Renderer)
	/// <summary>
	/// 模型Mesh
	/// </summary>
	shared_ptr<Mesh> mesh;

	/// <summary>
	/// 材质
	/// </summary>
	shared_ptr<Material> material;

	Renderer(Mesh*, Material*);
	Renderer();
	~Renderer();

	/// <summary>
	/// 进行渲染
	/// </summary>
	void Render();

	/// <summary>
	/// 被添加时
	/// </summary>
	void Awake() override;

	/// <summary>
	/// 序列化为xml
	/// </summary>
	/// <returns></returns>
	virtual TLxml* Serialize() override;

	/// <summary>
	/// 通过xml实例化
	/// </summary>
	/// <param name=""></param>
	virtual void Instantiate(TiXmlNode*) override;

	bool operator>(const Renderer& r)
	{
		return r.material->renderQueueIndex > material->renderQueueIndex;
	}
};
