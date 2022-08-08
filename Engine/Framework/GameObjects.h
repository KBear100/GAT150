#pragma once
#include "Math\Transform.h"

namespace Bear
{
	class GameObject
	{
	public:
		GameObject() = default;

		virtual void Update() = 0;
	};
}