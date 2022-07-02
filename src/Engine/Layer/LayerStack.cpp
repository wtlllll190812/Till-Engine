#include "TillPch.h"
#include "LayerStack.h"



LayerStack::LayerStack()
{
	mLayerInsert = mLayers.begin();
}

LayerStack::~LayerStack()
{
	for (auto layer : mLayers)
	{
		delete layer;
	}
}

void LayerStack::PushLayer(Layer* layer)
{
	layer->OnAttack();
	mLayerInsert = mLayers.emplace(mLayerInsert,layer);
}

void LayerStack::PushOverlay(Layer* layer)
{
	layer->OnAttack();
	mLayers.emplace_back(layer);
}

void LayerStack::PopLayer(Layer* layer)
{
	auto it = std::find(mLayers.begin(), mLayers.end(), layer);
	if (it != mLayers.end())
	{
		mLayers.erase(it);
		(*it)->OnDetach();
		mLayerInsert--;
	}
}

void LayerStack::PopOverlay(Layer* layer)
{
	auto it = std::find(mLayers.begin(), mLayers.end(), layer);
	if (it != mLayers.end())
	{
		(*it)->OnDetach();
		mLayers.erase(it);
	}
}
