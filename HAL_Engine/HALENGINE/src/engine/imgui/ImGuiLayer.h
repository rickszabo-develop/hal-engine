#pragma once

#include "engine/layer/Layer.h"
#include "engine/events/ApplicationEvent.h"
#include "engine/events/KeyEvent.h"
#include "engine/events/MouseEvent.h"

namespace Haleng {
	class HALENG_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& e);

		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);

		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnKeyReleased(KeyReleasedEvent& e);
		bool OnKeyTyped(KeyTypedEvent& e); //todo: implement typed

		bool OnWindowResize(WindowResizeEvent& e);
	private:
		float m_Time = 0.0f;
	};
	
}