#include "Engine.h"
#include "FinalGame.h"

using namespace std;

int main()
{
	Bear::InitializeMemory();
	Bear::SetFilePath("../Assets");

	// initialize systems
	Bear::g_renderer.Initialize();
	Bear::g_inputSystem.Initialize();
	Bear::g_audioSystem.Initialize();
	Bear::g_resources.Initialize();
	Bear::g_physicsSystem.Initialize();
	Bear::g_eventManager.Initialize();

	Bear::Engine::Instance().Register();

	// create window
	Bear::g_renderer.CreateWindow("Highway to Hell", 800, 600);
	Bear::g_renderer.SetClearColor(Bear::Color{ 0, 0, 0, 255 });

	// create game
	std::unique_ptr<FinalGame> game = std::make_unique<FinalGame>();
	game->Initialize();

	bool quit = false;
	while (!quit)
	{
		// update (engine)
		Bear::g_time.Tick();
		Bear::g_inputSystem.Update();
		Bear::g_audioSystem.Update();
		Bear::g_physicsSystem.Update();
		Bear::g_eventManager.Update();

		if (Bear::g_inputSystem.GetKeyDown(Bear::key_escape)) quit = true;

		// update scene
		game->Update();

		// render
		Bear::g_renderer.BeginFrame();

		game->Draw(Bear::g_renderer);

		Bear::g_renderer.EndFrame();
	}

	game->Shutdown();
	game.reset();

	Bear::Factory::Instance().Shutdown();

	Bear::g_eventManager.ShutDown();
	Bear::g_physicsSystem.Shutdown();
	Bear::g_resources.Shutdown();
	Bear::g_inputSystem.ShutDown();
	Bear::g_audioSystem.ShutDown();
	Bear::g_renderer.ShutDown();
}