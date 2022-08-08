#include "Engine.h"

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

	// create texture
	std::shared_ptr<Bear::Texture> texture = std::make_shared<Bear::Texture>();
	texture->Create(Bear::g_renderer, "Models/Fighter.png");

	Bear::Scene scene;

	// create actors
	Bear::Transform transform{ Bear::Vector2{100, 100}, 90, {3, 3} };

	std::unique_ptr<Bear::Actor> actor = std::make_unique <Bear::Actor>(transform);

	std::unique_ptr<Bear::PlayerComponent> pcomponent = std::make_unique<Bear::PlayerComponent>();
	actor->AddComponent(std::move(pcomponent));

	std::unique_ptr<Bear::SpriteComponent> scomponent = std::make_unique<Bear::SpriteComponent>();
	scomponent->m_texture = texture;
	actor->AddComponent(std::move(scomponent));

	scene.Add(std::move(actor));

	float angle = 0;

	bool quit = false;
	while (!quit)
	{
		// update (engine)
		Bear::g_time.Tick();
		Bear::g_inputSystem.Update();
		Bear::g_audioSystem.Update();

		if (Bear::g_inputSystem.GetKeyDown(Bear::key_escape)) quit = true;

		angle += 360.0f * Bear::g_time.deltaTime;

		// update scene
		scene.Update();

		// render
		Bear::g_renderer.BeginFrame();

		scene.Draw(Bear::g_renderer);
		Bear::g_renderer.Draw(texture, { 400, 300 }, angle, { 2, 2 }, { 0.5f, 1.0f });

		Bear::g_renderer.EndFrame();
	}

	Bear::g_renderer.ShutDown();
	Bear::g_audioSystem.ShutDown();
	Bear::g_inputSystem.ShutDown();
}