#pragma once

namespace Math
{
	const float Pi = 3.14159265359; // 180
	const float TwoPi = 6.28318530718; // 360
	const float HalfPi = 1.57079632679; // 90

	inline float DegToRad(float degrees)
	{
		return degrees * (Pi / 180);
	}

	inline float RadToDeg(float radians)
	{
		return radians * ( 180 / Pi );
	}

	int sqr(int v);
	inline int half(int v) { return v / 2; }
}