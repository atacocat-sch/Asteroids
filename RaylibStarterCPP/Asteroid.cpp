
#include "raymath.h"
#include "raylibAdapter.h"

#include "Utilities.h"
#include "Game.h"
#include "Asteroid.h"
#include "AsteroidPool.h"

#include <cmath>

using namespace Utilities;

void Asteroid::Split(Vector2 direction)
{
	if (size > 1)
	{
		Asteroid* asteroid = parentPool->GetAsteroid();
		asteroid->size = size - 1;
		asteroid->position = position + direction * size * 0.5f;
		asteroid->velocity = direction * bifricationForce;
		asteroid->RecalcVerticies();

		position -= direction * size * 0.5f;
		size--;
		velocity = -direction * bifricationForce;
		RecalcVerticies();
	}
	else
	{
		active = false;
	}
}

void Asteroid::Reset()
{
	active = true;
	age = 0.0f;

	size = (int)Remap(rand(), 0, RAND_MAX, 1, parentPool->maxSize);
	mass = size * size;

	float sceneHeight = mainGameScene.cameraSize + size * 2.0f;
	float sceneWidth = mainGameScene.cameraSize * ((float)GetScreenWidth() / GetScreenHeight()) + size * 2.0f;

	Vector2 direction;

	if (rand() % 2 == 0)
	{
		position = { sceneWidth * (rand() % 2 == 0 ? 1 : -1) / 2.0f, Remap(rand(), 0, RAND_MAX, sceneHeight / -2.0f, sceneHeight / 2.0f) };
		direction = { sceneWidth * -Sign(position.x) / 2.0f, Remap(rand(), 0, RAND_MAX, sceneHeight / -2.0f, sceneHeight / 2.0f) };
	}
	else
	{
		position = { Remap(rand(), 0, RAND_MAX, sceneWidth / -2.0f, sceneWidth / 2.0f), sceneHeight * (rand() % 2 == 0 ? 1 : -1) / 2.0f };
		direction = { Remap(rand(), 0, RAND_MAX, sceneWidth / -2.0f, sceneWidth / 2.0f), sceneHeight * -Sign(position.y) / 2.0f };
	}

	float speed = Remap(rand(), 0, RAND_MAX, speedMin, speedMax);
	velocity = Vector2Normalize(direction) * speed;

	RecalcVerticies();
}

void Asteroid::Update()
{
	float sceneHeight = mainGameScene.cameraSize + size * 2.0f;
	float sceneWidth = mainGameScene.cameraSize * ((float)GetScreenWidth() / GetScreenHeight()) + size * 2.0f;

	if (position.x - 0.1f > sceneWidth / 2.0f || position.x + 0.1f < sceneWidth / -2.0f)
	{
		active = false;
	}

	if (position.y - 0.1f > sceneHeight / 2.0f || position.y + 0.1f < sceneHeight / -2.0f)
	{
		active = false;
	}

	age += GetFrameTime();
}

void Asteroid::Draw()
{
	for (int i = 0; i < vertexCount; i++)
	{
		Vector2 a = position + verticies[i % vertexCount];
		Vector2 b = position + verticies[(i + 1) % vertexCount];

		DrawLineV(a, b, WHITE);
	}
}

Clonable* Asteroid::Clone()
{
	Asteroid* asteroid = new Asteroid();

	return asteroid;
}

void Asteroid::RecalcVerticies()
{
	for (int i = 0; i < vertexCount; i++)
	{
		float angleDelta = Remap(1, 0, vertexCount, 0.0f, 2.0f * PI);
		float angle = Remap(i, 0, vertexCount, 0.0f, 2.0f * PI) + Remap(rand(), 0, RAND_MAX, angleDelta / -2.0f, angleDelta / 2.0f);

		verticies[i] = Vector2{ cos(angle), sin(angle) } * size * 0.5f;
	}

	physicsShape = PhysicsShape(this, verticies, vertexCount);
}
