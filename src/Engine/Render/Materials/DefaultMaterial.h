#pragma once
#include "Material.h"

class Texture;
class DefaultMaterial:public Material
{
public:
	DefaultMaterial();
	~DefaultMaterial();

	virtual void OnRender(GameObject* gObj, std::shared_ptr<Mesh> mesh) override;
	virtual void BeforeRender(GameObject*, std::shared_ptr<Mesh> mesh) override;
private:
	Texture* tex;
	Texture* specTex;
};

