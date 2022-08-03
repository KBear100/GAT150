#pragma once
#include <memory>

namespace Bear
{
	class Renderer;
	class Scene;

	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;

		virtual void Initialize() = 0;
		virtual void Shutdown() = 0;

		virtual void Update() = 0;
		virtual void Draw(Renderer& renderer) = 0;

		int GetScore() { return m_score; }
		void AddPoints(int points) {m_score += points; }
		void LoseHealth(float health) { m_health -= health; }

	protected:
		std::unique_ptr<Scene> m_scene;
		int m_score = 0;
		float m_health = 3;
	};
}