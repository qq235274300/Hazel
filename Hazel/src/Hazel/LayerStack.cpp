#include "hzpch.h"
#include "LayerStack.h"

namespace Hazel
{
	LayerStack::LayerStack()
	{
		m_LayerInsert = begin();
	}
	LayerStack::~LayerStack()
	{
		for (auto layer : m_Layers)
		{
			delete layer;
		}
	}
	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerInsert = m_Layers.emplace(m_LayerInsert,layer);
	}
	void LayerStack::PushOverlay(Layer* layer)
	{
		m_Layers.emplace_back(layer);
	}
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it =std::find(begin(),end(),layer);
		if (it != end())
		{
			m_Layers.erase(it); //后面值会向前移动一位
			m_LayerInsert--;
		}
	}
	void LayerStack::PopOverlay(Layer* layer)
	{
		auto it = std::find(begin(), end(), layer);
		if (it != end())
		{
			m_Layers.erase(it);
		}
	}
}