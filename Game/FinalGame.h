#pragma once
#include "Framework/Game.h"
#include "Framework/Event.h"

class FinalGame : public Bear::Game, public Bear::INotify
{
public:
	enum class gameState
	{
		titleScreen,
		startLevel,
		game,
		playerDead,
		gameOver
	};

public:
	virtual void Initialize() override;
	virtual void Shutdown() override;
	virtual void Update() override;
	virtual void Draw(Bear::Renderer& renderer) override;
	virtual void OnNotify(const Bear::Event& event) override;

	void OnAddPoints(const Bear::Event& event);
	void OnPlayerDead(const Bear::Event& event);

private:
	gameState m_gameState = gameState::titleScreen;
	float m_stateTimer = 15.0f;
	int m_lives = 3;
};