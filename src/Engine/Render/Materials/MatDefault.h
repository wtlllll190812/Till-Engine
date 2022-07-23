#pragma once
#include "Material.h"

class Texture;
class DefaultMaterial:public Material
{
public:
	DefaultMaterial();
	~DefaultMaterial();

	virtual void DrawFunc(GameObject* gObj, std::shared_ptr<Mesh> mesh) override;
	virtual void Init(GameObject*, std::shared_ptr<Mesh> mesh) override;
private:
	Texture* mainTex;
	Texture* specTex;
};

