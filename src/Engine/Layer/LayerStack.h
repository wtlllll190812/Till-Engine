#pragma once
#include"Layer.h"

class LayerStack
{
public:
	LayerStack();
	~LayerStack();

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* layer);
	void PopLayer(Layer* layer);
	void PopOverlay(Layer* layer);

	std::vector<Layer*>::iterator begin() { return mLayers.begin(); }
	std::vector<Layer*>::iterator end() { return mLayers.end(); }
private:
	std::vector<Layer*> mLayers;
	std::vector<Layer*>::iterator mLayerInsert;
};

