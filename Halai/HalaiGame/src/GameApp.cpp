#include <Haleng.h>

class LayerExample : public Haleng::Layer {
public:
	LayerExample() {}
	~LayerExample() {}
};

class GameApp : public Haleng::Application 
{
	public:
		GameApp() 
		{
			PushLayer(new LayerExample());
			PushOverlay(new Haleng::ImGuiLayer());
		}

		~GameApp()
		{

		}
};

Haleng::Application* Haleng::CreateApplication() 
{
	return new GameApp();
}