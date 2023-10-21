#include "halpch.h"
#include "Application.h"

#include "engine/events/ApplicationEvent.h"
#include "engine/Log.h"

namespace Haleng 
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running) 
		{
			m_Window->OnUpdate();
		}
	}
}