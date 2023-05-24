#pragma once

#ifdef HALENG_PLATFORM_WINDOWS
extern Haleng::Application* Haleng::CreateApplication();

int main(int argc, char** argv) 
{
	auto game = Haleng::CreateApplication();
	game->Run();
	delete game;
}
#endif
