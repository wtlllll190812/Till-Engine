#pragma once
#include "Component.h"
#include "Material.h"
#include "Mesh.h"
#include <memory>

class GameObject;
class Renderer : public Component
{
public:
	COMPONENTNAME(Renderer)

	/// <summary>
	/// 模型Mesh
	/// </summary>
	std::shared_ptr<Mesh> mesh;

	/// <summary>
	/// 材质
	/// </summary>
	std::shared_ptr<Material> material;

	Renderer();
	~Renderer();

	/// <summary>
	/// 进行渲染
	/// </summary>
	void Draw();

	/// <summary>
	/// 被添加时
	/// </summary>
	void Awake() override;

	virtual void GuiDisPlay() override;

	bool operator>(const Renderer& r);

	/// <summary>
	/// 序列化
	/// </summary>
	virtual TiXmlElement* Serialize(std::string name = "Default") override;

	/// <summary>
	/// 反序列化
	/// </summary>
	virtual void DeSerialize(TiXmlElement*) override;

	virtual void UpdateNode() override;

private:
	void ChangeMaterial(std::shared_ptr<Material> mat);
private:
	std::string modelPath;
};
