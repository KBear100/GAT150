#pragma once
#include "GameObjects.h"

namespace Bear
{
	class Actor;
	
	class Component : public GameObject, public ISerializable
	{
	public:
		Component() = default;

		virtual void Update() = 0;
		virtual void Initialize() override {}

		friend class Actor;

	protected:
		Actor* m_owner = nullptr;
	};
}