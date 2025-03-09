#include <Haleng.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

//glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
//{
//	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
//	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
//	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
//	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
//	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
//	return Projection * View * Model;
//}

class LayerExample : public Haleng::Layer {
public:
	LayerExample()
		: Layer("Example") , m_Camera(60.0f, 1.778f, 0.1f, 100.0f)
	{
		m_Camera.SetPosition(glm::vec3(0.f, 0.f, -0.2f));
		m_Entity->SetPosition(glm::vec3(1.f, 0.f, 0.f));
	}
	~LayerExample() {}

	virtual void OnImGuiRender() override;
	virtual void OnUpdate(Haleng::Timestep deltaTime) override {
		Haleng::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Haleng::RenderCommand::Clear();

		if (Haleng::Input::IsKeyPressed(HAL_KEY_W)) 
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0.f, 0.f, 0.01f));
		
		else if (Haleng::Input::IsKeyPressed(HAL_KEY_S))
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0.f, 0.f, -0.01f));
		
		else if (Haleng::Input::IsKeyPressed(HAL_KEY_A)) 
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(-0.04f, 0.f, 0.f));
		
		else if (Haleng::Input::IsKeyPressed(HAL_KEY_D)) 
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0.04f, 0.f, 0.f));

		//draw entity
		Haleng::Renderer::BeginScene();

		m_Entity->GetShader().SetUniformMat4f("u_ViewProjectionMatrix", m_Camera.GetViewProjectionMatrix());
		m_Entity->GetShader().SetUniformMat4f("u_Transform", m_Entity->GetTransform());
		Haleng::Renderer::Submit(m_Entity->GetVertexArray());

		Haleng::Renderer::EndScene();
	}
private:
	Haleng::Camera m_Camera;
	Haleng::Entity* m_Entity = new Haleng::Entity();
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