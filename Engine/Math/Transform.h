#pragma once
#include "Vector2.h"
#include "Matrix2x2.h"
#include "Matrix3x3.h"

namespace Bear
{
	struct Transform
	{
		Vector2 position;
		float rotation{ 0 };
		Vector2 scale{1, 1};

		operator Matrix3x3() const
		{
			Matrix3x3 mxScale = Matrix3x3::CreateScale(scale);
			Matrix3x3 mxRotation = Matrix3x3::CreateRotation(Math::DegToRad(rotation));
			Matrix3x3 mxTranslation = Matrix3x3::CreateTranslation(position);

			return { mxScale * mxRotation * mxTranslation };
		}
	};
}