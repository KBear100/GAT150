#pragma once
#include "Renderer.h"
#include "../Math/Color.h"
#include <vector>
#include <string>

namespace Bear
{
	class Model
	{
	public:
		Model() = default;
		Model(const std::vector<Bear::Vector2>& points, const Bear::Color& color) : m_points{ points }, m_color{ color } {}
		Model(const std::string& filename);

		void Draw(Renderer& renderer, const Vector2& position, float angle, const float& scale = 1);

		void Load(const std::string filename);
		float CalculateRadius();

		float GetRadius() { return m_radius; }

	private:
		Bear::Color m_color {0, 0, 0, 0};
		std::vector<Bear::Vector2> m_points;

		float m_radius = 0;
	};
}