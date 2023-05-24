#include <Haleng.h>

class GameApp : public Haleng::Application 
{
	public:
		GameApp() 
		{

		}

		~GameApp()
		{

		}
};

Haleng::Application* Haleng::CreateApplication() 
{
	return new GameApp();
}