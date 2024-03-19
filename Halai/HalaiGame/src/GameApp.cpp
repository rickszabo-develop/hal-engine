#include <Haleng.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}

class LayerExample : public Haleng::Layer {
public:
	LayerExample()
		: Layer("Example") {
		auto foo = camera(5.0f, glm::vec2(0.5f, 0.5f));
	}
	~LayerExample() {}

	virtual void OnImGuiRender() override;
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