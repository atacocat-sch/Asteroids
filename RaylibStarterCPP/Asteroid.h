#pragma once

#include "PhysicsObject.h"

class AsteroidPool;

const int vertexCount = 8;

class Asteroid : public PhysicsObject
{
public:
	AsteroidPool* parentPool;

	const float speedMin = 3.0f;
	const float speedMax = 8.0f;
	const float bifricationForce = 5.0f;

	int size = 1;
	float age = 0.0f;
	Vector2 verticies[vertexCount];

	void Update();
	void Draw();

	void Split(Vector2 direction);
	void Reset();

	Clonable* Clone();

private:
	void RecalcVerticies();
};