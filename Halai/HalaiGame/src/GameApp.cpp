#include <Haleng.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


//Shaders
std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 m_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = m_ViewProjection * vec4(a_Position, 1.0);
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
//end of Shaders 

class LayerExample : public Haleng::Layer {
public:
	LayerExample()
		: Layer("Example"), m_Camera(-1.0, 1.0, -1.0, 1.0)
	{
		m_VertexArray.reset(Haleng::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f,	1.0f, 1.0f, 0.0f, 1.0f
		};

		std::shared_ptr<Haleng::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Haleng::VertexBuffer::Create(vertices, sizeof(vertices)));

		Haleng::BufferLayout layout = {
			{ Haleng::ShaderDataType::Float3, "a_Position" },
			{ Haleng::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);

		uint32_t indices[3] = { 0, 1, 2 };

		std::shared_ptr<Haleng::IndexBuffer> indexBuffer;
		indexBuffer.reset(Haleng::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_Shader.reset(new Haleng::Shader(vertexSrc, fragmentSrc));
	}
	~LayerExample() {}

	void OnUpdate() 
	{
		Haleng::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Haleng::RenderCommand::Clear();
		Haleng::Renderer::BeginScene();

		m_Camera.SetPosition({ 0.5f, 0.5f, 0.0f });

		m_Shader->Bind();
		m_Shader->UploadUniformMat4("m_ViewProjection", m_Camera.GetViewProjectionMatrix());

		Haleng::Renderer::Submit(m_VertexArray);
		Haleng::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override;
private:
	Haleng::OrthographicCamera m_Camera;
	std::shared_ptr<Haleng::VertexArray> m_VertexArray;
	std::shared_ptr<Haleng::Shader> m_Shader;
};

void LayerExample::OnImGuiRender() 
{
	
}

class GameApp : public Haleng::Application 
{
	public:
		GameApp() : Haleng::Application()
		{
			PushLayer(new LayerExample());
		}

		~GameApp()
		{

		}
};



Haleng::Application* Haleng::CreateApplication() 
{
	return new GameApp();
}