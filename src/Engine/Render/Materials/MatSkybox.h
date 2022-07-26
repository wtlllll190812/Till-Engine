#pragma once
#include "Material.h"

class Texture;
class MatSkybox :public Material
{
public:
	MatSkybox();
	~MatSkybox();

	virtual void DrawFunc(GameObject* gObj, std::shared_ptr<Mesh> mesh) override;
	virtual void Init(GameObject*, std::shared_ptr<Mesh> mesh) override;
private:
	Texture* skybox;
};

