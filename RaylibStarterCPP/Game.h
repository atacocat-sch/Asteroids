#pragma once

#include "PhysicsWorld.h"

#include "raylib.h"
#include <vector>

class Updatable;
class Game;
extern Game* mainGameScene;

class Game
{
public:
	Game();
	Game& operator= (const Game& other);
	~Game();

	void Update();

	void Register(Updatable* updatable);

	Camera2D camera;
	float cameraSize = 20.0f;

	PhysicsWorld physicsWorld;

private:
	std::vector<Updatable*> updatableObjects;
};