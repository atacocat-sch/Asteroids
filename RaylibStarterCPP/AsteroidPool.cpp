
#include "AsteroidPool.h"
#include "Game.h"

#include <algorithm>

using std::max;
using std::min;

AsteroidPool::AsteroidPool()
{
	for (int i = 0; i < asteroidPoolSize; i++)
	{
		asteroids[i] = new Asteroid();
		asteroids[i]->active = false;
		asteroids[i]->parentPool = this;
	}
}

void AsteroidPool::Update()
{
	float deltaTime = GetFrameTime();

	int activeAsteroids = 0;
	for (int i = 0; i < asteroidPoolSize; i++)
	{
		if (asteroids[i]->active)
		{
			activeAsteroids++;
		}
	}

	for (int i = 0; i < minAsteroids - activeAsteroids; i++)
	{
		GetAsteroid();
	}

	minAsteroids = min(minAsteroidOffset + minAsteroidIncrease * mainGameScene.sceneTime, minAsteroidMax);
	maxSize = min(maxSizeOffset + maxSizeIncrease * mainGameScene.sceneTime, minAsteroidMax);
}

Asteroid* AsteroidPool::GetAsteroid()
{
	Asteroid* target = nullptr;

	for (int i = 0; i < asteroidPoolSize; i++)
	{
		if (!asteroids[i]->active)
		{
			target = asteroids[i];
			break;
		}
	}

	if (target == nullptr)
	{
		target = asteroids[0];
		for (int i = 1; i < asteroidPoolSize; i++)
		{
			if (asteroids[i]->age > target->age)
			{
				target = asteroids[i];
			}
		}
	}

	target->Reset();
	return target;
}

Clonable* AsteroidPool::Clone()
{
	AsteroidPool* newPool = new AsteroidPool();

	return newPool;
}