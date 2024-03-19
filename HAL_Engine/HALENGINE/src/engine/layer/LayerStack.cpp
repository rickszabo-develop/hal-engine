#include "halpch.h"
#include "LayerStack.h"


namespace Haleng {
	LayerStack::LayerStack() {}

	LayerStack::~LayerStack() 
	{
		for (Layer* l : m_Layers) 
		{
			delete l;
		}
	}

	void LayerStack::PushLayer(Layer* layer) 
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay) 
	{
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer) 
	{
		auto it = std::find(begin(), end(), layer);
		if (it != end()) 
		{
			m_Layers.erase(it);
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