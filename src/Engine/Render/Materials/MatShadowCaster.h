#pragma once
#include "Material.h"

class MatShadowCaster :public Material
{
public:
	MatShadowCaster();
	~MatShadowCaster();

	virtual void DrawFunc(GameObject* gObj, std::shared_ptr<Mesh> mesh) override;
	virtual void Init(GameObject*, std::shared_ptr<Mesh> mesh) override;
};
