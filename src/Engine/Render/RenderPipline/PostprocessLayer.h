#pragma once 
#include "Material.h"
#include "Layer.h"

class FrameBuffer;
class PostprocessLayer :public Layer
{
public:
	PostprocessLayer();
	~PostprocessLayer();

	virtual void OnAttack()override;
	virtual void OnDetach()override;
	virtual void OnUpdate()override;

	inline const std::string& GetName()const { return "PostprocessLayer"; }

private:
	FrameBuffer* buffer;
	Shader* shader;
	static float quadVertices[];
};

