#pragma once
#include "Core.h"
#include "events/Event.h"
#include "Window.h"

namespace Haleng {
	class HALENG_API Application
	{
		public:
			Application();
			virtual ~Application();

			void Run();

			void OnEvent(Event&);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	Application* CreateApplication();
}