#pragma once
#include "Material.h"
class Texture;
class MatPBR :public Material
{
public:
	MatPBR();
	~MatPBR();
	glm::vec3 albedo=glm::vec3(1);
	float metallic = 0.3;
	float roughness = 0.3;
	float ao = 1;

	virtual void DrawFunc(GameObject* gObj, std::shared_ptr<Mesh> mesh) override;
	virtual void Init(GameObject*, std::shared_ptr<Mesh> mesh) override;
	virtual void GuiDisPlay() override;
private:
	Texture* mainTex;
	Texture* specTex;
	Texture* normalTex;
};

