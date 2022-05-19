#pragma once

#include "raylib.h"
#include "raymath.h"

Vector2 operator+(Vector2 a, Vector2 b);
Vector2& operator+=(Vector2& a, Vector2 b);

Vector2 operator - (Vector2 a, Vector2 b);
Vector2& operator -= (Vector2& a, Vector2 b);

Vector2 operator* (Vector2 v, float s);
Vector2& operator*= (Vector2& v, float s);

Vector2 FromPolar(float a, float d);
Vector2 FromPolarDeg(float a, float d);