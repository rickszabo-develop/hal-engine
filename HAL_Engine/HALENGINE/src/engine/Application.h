#pragma once
#include "Core.h"
#include "events/Event.h"
#include "events/ApplicationEvent.h"
#include "Window.h"
#include "layer/Layer.h"
#include "layer/LayerStack.h"

namespace Haleng {
	class HALENG_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event&);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		LayerStack m_LayerStack;
	};

	Application* CreateApplication();
}