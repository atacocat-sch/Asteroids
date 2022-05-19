#include "raylib.h"
#include "raymath.h"
#include <cmath>

Vector2 operator+(Vector2 a, Vector2 b)
{
	return Vector2Add(a, b);
}

Vector2& operator+=(Vector2& a, Vector2 b)
{
	a = Vector2Add(a, b);
	return a;
}

Vector2 operator - (Vector2 a, Vector2 b)
{
	return Vector2Subtract(a, b);
}

Vector2& operator -= (Vector2& a, Vector2 b)
{
	a = Vector2Subtract(a, b);
	return a;
}

Vector2 operator* (Vector2 v, float s)
{
	return Vector2Scale(v, s);
}

Vector2& operator*= (Vector2& v, float s)
{
	v = Vector2Scale(v, s);
	return v;
}

Vector2 FromPolar(float a, float d)
{
	return { cos(a) * d, sin(a) * d };
}

Vector2 FromPolarDeg(float a, float d)
{
	return FromPolar(a / 180.0f * PI, d);
}