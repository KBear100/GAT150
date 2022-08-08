#pragma once
#include "Framework/Component.h"

namespace Bear
{
	class PlayerComponent : public Component
	{
	public:
		PlayerComponent() = default;

		void Update() override;

	private:

	};
}