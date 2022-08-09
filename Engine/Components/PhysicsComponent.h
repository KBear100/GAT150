#pragma once
#include "Framework/Component.h"

namespace Bear
{
	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent() = default;

		void Update() override;

		void ApplyForce(const Vector2& force) { m_acceleration += force; }

	public:
		Vector2 m_velocity;
		Vector2 m_acceleration;

		float m_damping = 1;
	};
}