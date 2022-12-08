#include "pch.h"
#include "Math.h"
#include <math.h>

float Lerp(float start, float end, float value)
{
	float fixValue = end - start;
	return start + (value * fixValue);
}

float Abs(float value)
{
	if (value < -1) value = value * -1;

	return value;
}

float Clamp(float value, float min, float max)
{
	if (value < min) value = min;
	if (value > max) value = max;

	return value;
}

Vector2 Lerp(Vector2 start, Vector2 end, float value)
{
	Vector2 fixValue = end - start;

	return start + (fixValue * value);
}

float Angle(Vector2 a, Vector2 b)
{
	return atan(b.y / b.x) - atan(a.y / a.x);
}

Vector2 Normalize(Vector2 value)
{
	if (value.x != 0 || value.y != 0) 
	{
		float size = sqrt(pow(value.x, 2) + pow(value.y, 2));
		value = value / size;
	}

	return Vector2(value.x, value.y);
}

float Distance(Vector2 a, Vector2 b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

float Magnitude(Vector2 value)
{
	return sqrt(pow(value.x, 2) + pow(value.y, 2));
}
