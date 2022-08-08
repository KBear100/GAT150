#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>

namespace Bear
{
	void PlayerComponent::Update()
	{
		if (Bear::g_inputSystem.GetKeyDown(key_up))
		{
			m_owner->m_transform.position.y -= 3;
		}

		if (Bear::g_inputSystem.GetKeyDown(key_down))
		{
			m_owner->m_transform.position.y += 3;
		}

		if (Bear::g_inputSystem.GetKeyDown(key_right))
		{
			m_owner->m_transform.position.x += 3;
		}

		if (Bear::g_inputSystem.GetKeyDown(key_left))
		{
			m_owner->m_transform.position.x -= 3;
		}
	}
}