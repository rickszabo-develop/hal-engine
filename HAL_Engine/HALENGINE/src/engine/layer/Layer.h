#pragma once

#include "engine/Core.h"
#include "engine/events/Event.h"
#include "engine/core/Timestep.h"

namespace Haleng {

	class HALENG_API Layer 
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnEvent(Event& e) {}
		virtual void OnUpdate(Timestep deltaTime) {}
		virtual void OnImGuiRender() {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}