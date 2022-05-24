#pragma once

#include "Updatable.h"
#include "Asteroid.h"

const int asteroidPoolSize = 30;

class AsteroidPool : public Updatable
{
public:
	int minAsteroids = 6;
	int maxSize = 3;

	const float minAsteroidIncrease = 0.1f;
	const float maxSizeIncrease = 0.1f;
	const float minAsteroidOffset = 6.0f;
	const float maxSizeOffset = 3.0f;

	AsteroidPool();

	void Update();

	Asteroid* GetAsteroid();

	Clonable* Clone();

private:
	Asteroid* asteroids[asteroidPoolSize];
};