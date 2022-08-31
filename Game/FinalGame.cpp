#include "FinalGame.h"
#include "GameComponents/EnemyComponent.h"
#include "Engine.h"


void FinalGame::Initialize()
{
	REGISTER_CLASS(EnemyComponent);

	m_scene = std::make_unique<Bear::Scene>();

	rapidjson::Document document;
	std::vector<std::string> sceneNames = {"Scenes/prefabs.txt", "Scenes/tilemap.txt", "Scenes/level.txt" };

	for (auto sceneName : sceneNames)
	{
		bool success = Bear::json::Load(sceneName, document);
		if (!success)
		{
			LOG("Could not load scene %s", sceneName.c_str());
			continue;
		}

		m_scene->Read(document);
	}
	m_scene->Initialize();

	Bear::g_eventManager.Subscribe("EVENT ADD POINTS", std::bind(&FinalGame::OnNotify, this, std::placeholders::_1));
	Bear::g_eventManager.Subscribe("EVENT_PLAYER_DEAD", std::bind(&FinalGame::OnNotify, this, std::placeholders::_1));
}

void FinalGame::Shutdown()
{
	m_scene->RemoveAll();
}

void FinalGame::Update()
{
	switch (m_gameState)
	{
	case FinalGame::gameState::titleScreen:
		if (Bear::g_inputSystem.GetKeyState(Bear::key_space) == Bear::InputSystem::KeyState::Pressed)
		{
			m_scene->GetActorFromName("Title")->SetActive(false);

			m_gameState = gameState::startLevel;
		}
		break;

	case FinalGame::gameState::startLevel:
		for (int i = 0; i < 10; i++)
		{
			auto actor = Bear::Factory::Instance().Create<Bear::Actor>("Coin");
			actor->m_transform.position = { Bear::randomf(0, 600), 100.0f };
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}
		for (int i = 0; i < 3; i++)
		{
			auto actor = Bear::Factory::Instance().Create<Bear::Actor>("Ghost");
			actor->m_transform.position = { Bear::randomf(0, 600), 100.0f };
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}
		{
			auto actor = Bear::Factory::Instance().Create<Bear::Actor>("Player");
			actor->m_transform.position = { Bear::randomf(0, 600), 100.0f };
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}
		m_gameState = gameState::game;
		break;

	case FinalGame::gameState::game:
		break;

	case FinalGame::gameState::playerDead:
		m_stateTimer -= Bear::g_time.deltaTime;
		if (m_stateTimer <= 0)
		{
			m_gameState = (m_lives > 0) ? gameState::startLevel : m_gameState = gameState::gameOver;
		}
		break;

	case FinalGame::gameState::gameOver:
		break;

	default:
		break;
	}

	m_scene->Update();
}

void FinalGame::Draw(Bear::Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void FinalGame::OnAddPoints(const Bear::Event& event)
{
	AddPoints(std::get<int>(event.data));

	std::cout << event.name << std::endl;
	std::cout << GetScore() << std::endl;
}

void FinalGame::OnPlayerDead(const Bear::Event& event)
{
	m_gameState = gameState::playerDead;
	m_lives--;
	m_stateTimer = 3.0f;
}

void FinalGame::OnNotify(const Bear::Event& event)
{
	if (event.name == "EVENT ADD POINTS")
	{
		AddPoints(std::get<int>(event.data));
	}

	if (event.name == "EVENT_PLAYER_DEAD")
	{
		m_gameState = gameState::playerDead;
		m_lives--;
		m_stateTimer = 3.0f;
	}
}
