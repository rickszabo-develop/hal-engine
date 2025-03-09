#include "halpch.h"
#include "Application.h"

#include "engine/Log.h"
#include "engine/Input.h"
#include "engine/renderer/Shader.h"
#include "engine/renderer/Renderer.h"
#include "renderer/BufferLayout.h"
#include "engine/scene/Camera.h"
#include "engine/Keycodes.h"
#include "platform/windows/WindowsInput.h"
#include "engine/scene/Entity.h"
#include <glm/ext/matrix_transform.hpp>

namespace Haleng {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		HALENG_CORE_INFO("{0}", e.ToString());

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) 
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}

		EventDispatcher dispatch(e);
		dispatch.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
	}

	void Application::PushLayer(Layer* layer) 
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) 
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::Run()
	{
		Camera camera(60.0f, 1.778f, 0.1f, 100.0f);
		camera.SetPosition(glm::vec3(0.f, 0.f, -0.2f));

		Entity* entity = new Entity();
		entity->SetPosition(glm::vec3(1.f, 0.f, 0.f));

		Entity* entity1 = new Entity();
		entity1->SetPosition(glm::vec3(-1.f, 0.f, 0.f));

		Entity* entity2 = new Entity();
		entity2->SetPosition(glm::vec3(0.f, 0.f, 0.f));

		while (m_Running) 
		{
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			if (WindowsInput::IsKeyPressed(HAL_KEY_W)) {
				camera.SetPosition(camera.GetPosition() + glm::vec3(0.f, 0.f, 0.01f));
			}
			else if (WindowsInput::IsKeyPressed(HAL_KEY_S))
			{
				camera.SetPosition(camera.GetPosition() + glm::vec3(0.f, 0.f, -0.01f));
			}
			else if (WindowsInput::IsKeyPressed(HAL_KEY_A)) {
				camera.SetPosition(camera.GetPosition() + glm::vec3(-0.04f, 0.f, 0.f));
			}
			else if (WindowsInput::IsKeyPressed(HAL_KEY_D)) {
				camera.SetPosition(camera.GetPosition() + glm::vec3(0.04f, 0.f, 0.f));
			}

			//draw entity
			Renderer::BeginScene();
			entity->GetShader().SetMat4("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
			entity->GetShader().SetMat4("u_Transform", entity->GetTransform());
			Renderer::Submit(entity->GetVertexArray());

			//draw entity1
			entity1->GetShader().SetMat4("u_Transform", entity1->GetTransform());
			Renderer::Submit(entity1->GetVertexArray());

			//draw entity2
			entity1->GetShader().SetMat4("u_Transform", entity2->GetTransform());
			Renderer::Submit(entity2->GetVertexArray());
			Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}