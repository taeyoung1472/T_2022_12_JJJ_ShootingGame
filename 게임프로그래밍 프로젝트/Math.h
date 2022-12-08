#pragma once
#include "Vector2.h"

float Lerp(float start, float end, float value);
float Abs(float value);
float Clamp(float value, float min, float max);

Vector2 Lerp(Vector2 start, Vector2 end, float value);
float Angle(Vector2 a, Vector2 b);
Vector2 Normalize(Vector2 value);
float Distance(Vector2 a, Vector2 b);
float Magnitude(Vector2 value);