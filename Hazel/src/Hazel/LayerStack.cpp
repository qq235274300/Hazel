#include "hzpch.h"
#include "LayerStack.h"

namespace Hazel
{
	LayerStack::LayerStack()
	{
	
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
		 m_Layers.emplace(begin() + m_LayerInsertIndex ,layer);
		 m_LayerInsertIndex++;
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
			m_LayerInsertIndex--;
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