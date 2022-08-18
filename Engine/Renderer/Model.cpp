#include "Model.h"
#include "Core/File.h"
#include "Core/Logger.h"
#include "Math/Transform.h"
#include <sstream>
#include <iostream>

namespace Bear
{
	Model::Model(const std::string& filename)
	{
		Load(filename);
		m_radius = CalculateRadius();
	}

	bool Model::Create(std::string filename, ...)
	{
		if (!Load(filename))
		{
			LOG("Error could not create file %s", filename.c_str());
			return false;
		}

		return true;
	}

	void Model::Draw(Renderer& renderer, const Vector2& position, float angle, const Vector2& scale)
	{
		//draw model
		for (int i = 0; i < m_points.size() - 1; i++)
		{
			Bear::Vector2 p1 = Vector2::Rotate((m_points[i] * scale), angle) + position;
			Bear::Vector2 p2 = Vector2::Rotate((m_points[i + 1] * scale), angle) + position;

			renderer.DrawLine(p1, p2, m_color);
		}
	}

	void Model::Draw(Renderer& renderer, const Transform& transform)
	{
		Matrix3x3 mx = transform.matrix;
		//if (m_points.size() == 0) return;

		//draw model
		for (int i = 0; i < m_points.size() - 1; i++)
		{
			Bear::Vector2 p1 = mx * m_points[i];
			Bear::Vector2 p2 = mx * m_points[i + 1];

			renderer.DrawLine(p1, p2, m_color);
		}
	}

	bool Model::Load(const std::string filename)
	{
		std::string buffer;

		if (!Bear::ReadFile(filename, buffer))
		{
			LOG("Error could not read file %s", filename.c_str());
			return false;
		}

		//read color
		std::istringstream stream(buffer);
		stream >> m_color;

		//read number of points
		std::string line;
		std::getline(stream, line);

		//get number of points
		size_t numPoints = std::stoi(line);

		// read model points
		for (size_t i = 0; i < numPoints; i++)
		{
			Vector2 point;

			stream >> point;
			m_points.push_back(point);
		}

		return true;
	}

	float Model::CalculateRadius()
	{
		float radius = 0;

		// find the largest length
		for (auto& point : m_points)
		{
			if (point.Length() > radius) radius = point.Length();
		}

		return radius;
	}
}