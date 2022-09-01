#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>

namespace Bear
{
	void PlayerComponent::Initialize()
	{
		CharacterComponent::Initialize();
	}

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

		Vector2 velocity;
		auto component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			// if in the air (m_groundCount == 0) then reduce force
			float multiplier = (m_groundCount > 0) ? 1 : 0.2f;

			component->ApplyForce(direction * speed * multiplier);
			velocity = component->velocity;
		}

		if (m_groundCount > 0 && g_inputSystem.GetKeyState(key_space) == InputSystem::KeyState::Pressed)
		{
			auto component = m_owner->GetComponent<PhysicsComponent>();
			if (component)
			{
				component->ApplyForce(Vector2::up * jump);
				velocity = component->velocity;
			}
		}

		auto animComponent = m_owner->GetComponent<SpriteAnimComponent>();
		if (animComponent)
		{
			if (velocity.x != 0) animComponent->SetFlipHorizontal(velocity.x < 0);
			if (std::fabs(velocity.x) > 0)
			{
				animComponent->SetSequence("run");
			}
			else
			{
				animComponent->SetSequence("idle");
			}

			if (m_groundCount <= 0)
			{
				animComponent->SetSequence("jump");
			}
		}

		// set camera
		auto camera = m_owner->GetScene()->GetActorFromName("Camera");
		if (camera)
		{
			camera->m_transform.position = Math::Lerp(camera->m_transform.position, m_owner->m_transform.position, 2 * g_time.deltaTime);
		}
	}

	bool PlayerComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool PlayerComponent::Read(const rapidjson::Value& value)
	{
		CharacterComponent::Read(value);
		READ_DATA(value, jump);

		return true;
	}

	void PlayerComponent::OnNotify(const Event& event)
	{
		if (event.name == "EVENT_DAMAGE")
		{
			health -= std::get<float>(event.data);
			auto textHealth = m_owner->GetScene()->GetActorFromName("Health")->GetComponent<TextComponent>();
			textHealth->SetText(std::to_string(health));
			std::cout << health << std::endl;
			if (health <= 0)
			{
				m_owner->SetDestroy();

				Event event;
				event.name = "EVENT_PLAYER_DEAD";

				g_eventManager.Notify(event);
			}
		}
	}

	void PlayerComponent::OnCollisionEnter(Actor* other)
	{
		if (other->GetTag() == "Ground")
		{
			m_groundCount++;
		}

		if (other->GetName() == "Coin")
		{
			Event event;
			event.name = "EVENT ADD POINTS";
			event.data = 100;

			g_eventManager.Notify(event);

			g_audioSystem.PlayAudio("CoinGrab"); 

			other->SetDestroy();
		}

		/*if (other->GetTag() == "Enemy")
		{
			Event event;
			event.name = "EVENT_DAMAGE";
			event.data = damage;
			event.receiver = other;

			g_eventManager.Notify(event);
		}*/
	}

	void PlayerComponent::OnCollisionExit(Actor* other)
	{
		if (other->GetTag() == "Ground")
		{
			m_groundCount--;
		}
	}
}