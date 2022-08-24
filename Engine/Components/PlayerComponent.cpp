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

		if (Bear::g_inputSystem.GetKeyState(key_down) == InputSystem::KeyState::Held)
		{
			direction = Vector2::down;
		}

		if (Bear::g_inputSystem.GetKeyState(key_right) == InputSystem::KeyState::Held)
		{
			direction = Vector2::right;
		}

		if (Bear::g_inputSystem.GetKeyState(key_left) == InputSystem::KeyState::Held)
		{
			direction = Vector2::left;
		}

		auto component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			component->ApplyForce(direction * speed);
		}

		if (g_inputSystem.GetKeyState(key_space) == InputSystem::KeyState::Pressed)
		{
			auto component = m_owner->GetComponent<PhysicsComponent>();
			if (component)
			{
				component->ApplyForce(Vector2::up * 500);
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