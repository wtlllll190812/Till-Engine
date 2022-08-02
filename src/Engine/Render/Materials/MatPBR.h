#pragma once
#include "Material.h"

class Texture;
class MatPBR :public Material
{
public:
	MatPBR();
	~MatPBR();

	virtual void DrawFunc(GameObject* gObj, std::shared_ptr<Mesh> mesh) override;
	virtual void Init(GameObject*, std::shared_ptr<Mesh> mesh) override;
private:
	Texture* mainTex;
	Texture* specTex;
	Texture* normalTex;
};

