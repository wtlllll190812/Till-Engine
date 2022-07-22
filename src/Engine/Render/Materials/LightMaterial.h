#pragma once
#include "Material.h"

class LightMaterial:public Material
{
public:
	LightMaterial();
	~LightMaterial();

	virtual void DrawFunc(GameObject* gObj, std::shared_ptr<Mesh> mesh) override;
	virtual void Init(GameObject*, std::shared_ptr<Mesh> mesh) override;
};
