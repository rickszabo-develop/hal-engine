#include "halpch.h"
#include "Application.h"

#include "engine/Log.h"
#include "engine/Input.h"
#include "engine/renderer/Shader.h"

#include <glad/glad.h>
#include "renderer/BufferLayout.h"

namespace Haleng {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) 
	{
		switch (type)
		{
		case Haleng::ShaderDataType::None:		
		case Haleng::ShaderDataType::Float:		return GL_FLOAT;
		case Haleng::ShaderDataType::Float2:	return GL_FLOAT;
		case Haleng::ShaderDataType::Float3:	return GL_FLOAT;
		case Haleng::ShaderDataType::Float4:	return GL_FLOAT;
		case Haleng::ShaderDataType::Mat3:		return GL_FLOAT;
		case Haleng::ShaderDataType::Mat4:		return GL_FLOAT;
		case Haleng::ShaderDataType::Int:		return GL_INT;
		case Haleng::ShaderDataType::Int2:		return GL_INT;
		case Haleng::ShaderDataType::Int3:		return GL_INT;
		case Haleng::ShaderDataType::Int4:		return GL_INT;
		case Haleng::ShaderDataType::Bool:		return GL_BOOL;
		}

		HALENG_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Application::Application()
	{
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);


		// -- first triangle
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f,	1.0f, 1.0f, 0.0f, 1.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, 21 * sizeof(float)));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};

		m_VertexBuffer->SetLayout(layout);

		int index = 0;
		for(const auto& element : m_VertexBuffer->GetLayout().GetElements())
		{
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized, layout.GetStride(), (const void*)element.Offset);
			glEnableVertexAttribArray(index);
			index++;
		}

		uint32_t indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));
		
		// -- end first triangle

		// -- start shader 
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
		// -- end shader
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
		while (m_Running) 
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();

			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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