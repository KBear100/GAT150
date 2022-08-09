#pragma once
#include "GameObjects.h"

namespace Bear
{
	class Actor;
	
	class Component : public GameObject
	{
	public:
		Component() = default;

		virtual void Update() = 0;

		friend class Actor;

	protected:
		Actor* m_owner = nullptr;
	};
}