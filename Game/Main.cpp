#include "Engine.h"
#include <iostream>

using namespace std;

int main()
{
	Bear::InitializeMemory();
	Bear::SetFilePath("../Assets");

	// initialize systems
	Bear::g_renderer.Initialize();
	Bear::g_inputSystem.Initialize();
	Bear::g_audioSystem.Initialize();

	// create window
	Bear::g_renderer.CreateWindow("Test", 800, 600);
	Bear::g_renderer.SetClearColor(Bear::Color{ 0, 0, 0, 255 });

	//create texture
	std::shared_ptr<Bear::Texture> texture = std::make_shared<Bear::Texture>();
	texture->Create(Bear::g_renderer, "Models/Fighter.png");

	bool quit = false;
	while (!quit)
	{
		//update (engine)
		Bear::g_time.Tick();
		Bear::g_inputSystem.Update();
		Bear::g_audioSystem.Update();

		if (Bear::g_inputSystem.GetKeyDown(Bear::key_escape)) quit = true;

		//render
		Bear::g_renderer.BeginFrame();

		Bear::g_renderer.Draw(texture, { 400, 300 }, 0);

		Bear::g_renderer.EndFrame();
	}

	Bear::g_renderer.ShutDown();
	Bear::g_audioSystem.ShutDown();
	Bear::g_inputSystem.ShutDown();
}