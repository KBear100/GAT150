#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>

namespace Bear
{
	void PlayerComponent::Update()
	{
		Vector2 direction = Vector2::zero;

		float thrust = 0;
		if (Bear::g_inputSystem.GetKeyState(key_up) == InputSystem::KeyState::Held)
		{
			thrust = speed;
		}

		auto component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			// thrust force
			Vector2 force = Vector2::Rotate({ 1, 0 }, Math::DegToRad(m_owner->m_transform.rotation)) * thrust;
			component->ApplyForce(force);

			// gravitational force
			//force = (Vector2{ 400, 300 } - m_owner->m_transform.position).Normalized() * 60.0f;
			//component->ApplyForce(force);
		}

		if (Bear::g_inputSystem.GetKeyState(key_down) == InputSystem::KeyState::Held)
		{
			//m_owner->m_transform.position.y += 1;
			direction += Vector2::down;
		}

		if (Bear::g_inputSystem.GetKeyState(key_right) == InputSystem::KeyState::Held)
		{
			m_owner->m_transform.rotation += 180 * g_time.deltaTime;
		}

		if (Bear::g_inputSystem.GetKeyState(key_left) == InputSystem::KeyState::Held)
		{
			m_owner->m_transform.rotation -= 180 * g_time.deltaTime;
		}

		m_owner->m_transform.position += direction * 300 * g_time.deltaTime;

		if (g_inputSystem.GetKeyState(key_space) == InputSystem::KeyState::Pressed)
		{
			auto component = m_owner->GetComponent<AudioComponent>();
			if (component)
			{
				component->Play();
			}
		}
	}

	bool PlayerComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool PlayerComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, speed);

		return true;
	}
}