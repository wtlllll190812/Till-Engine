#pragma once
#include "Material.h"

class DefaultMaterial:public Material
{
public:
	DefaultMaterial();
	~DefaultMaterial();

	virtual void RenderCallback(GameObject*, Shader*, Material*) override;
};

