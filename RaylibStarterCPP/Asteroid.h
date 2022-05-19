#pragma once

#include "PhysicsObject.h"

class AsteroidPool;

const int vertexCount = 16;

class Asteroid : public PhysicsObject
{
public:
	AsteroidPool* parentPool;

	const float speedMin = 3.0f;
	const float speedMax = 8.0f;

	int size = 1;
	float age = 0.0f;
	Vector2 verticies[vertexCount];

	void Update();
	void Draw();

	void Reset();

	Clonable* Clone();
};