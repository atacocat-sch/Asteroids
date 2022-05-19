#include "raylib.h"
#include "Game.h"
#include "Player.h"
#include "AsteroidPool.h"

#include <vector>

int main()
{
	Game game;

	Player* player = new Player();

	AsteroidPool* asteroidPool = new AsteroidPool();

	InitWindow(1280, 720, "Definitely not just a blatant rip-off of the hit 1980's game Asteroids");

	SetTargetFPS(144);

	while (!WindowShouldClose())
	{
		game.Update();
	}

	return 0;
}