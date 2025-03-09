#pragma once
#include "Core.h"
#include "events/Event.h"
#include "events/ApplicationEvent.h"
#include "Window.h"
#include "layer/Layer.h"
#include "layer/LayerStack.h"
#include "engine/renderer/Shader.h"
#include "engine/renderer/VertexBuffer.h"
#include "engine/renderer/IndexBuffer.h"
#include "renderer/VertexArray.h"

#include "imgui/ImGuiLayer.h"



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

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;

		//std::unique_ptr<Shader> m_Shader;
		//std::shared_ptr<VertexArray> m_VertexArray;

		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	Application* CreateApplication();
}