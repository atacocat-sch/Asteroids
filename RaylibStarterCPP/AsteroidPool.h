#pragma once

#include "Updatable.h"
#include "Asteroid.h"

const int asteroidPoolSize = 30;

class AsteroidPool : public Updatable
{
public:
	int minAsteroids = 6;
	int maxSize = 3;

	AsteroidPool();

	void Update();

	Clonable* Clone();

private:
	Asteroid* asteroids[asteroidPoolSize];

	Asteroid* GetAsteroid();
};