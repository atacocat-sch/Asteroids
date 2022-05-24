#include "raylib.h"
#include "Game.h"
#include "Player.h"
#include "AsteroidPool.h"

#include <vector>

int main()
{
	LoadTitleScene();

	InitWindow(1280, 720, "Definitely not just a blatant rip-off of the hit 1980's game Asteroids");

	SetTargetFPS(144);

	while (!WindowShouldClose())
	{
		mainGameScene.Update();
	}

	return 0;
}