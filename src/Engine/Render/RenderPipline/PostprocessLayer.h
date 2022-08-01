#pragma once 
#include "Layer.h"

class FrameBuffer;
class Shader;
class PostprocessLayer :public Layer
{
public:
	PostprocessLayer(FrameBuffer*);
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

