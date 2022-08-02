#pragma once 
#include "Layer.h"
#include <memory>

class FrameBuffer;
class Shader;
class Mesh;
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
	static std::shared_ptr<Mesh> quadMesh;
};