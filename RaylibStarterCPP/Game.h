#pragma once

#include "PhysicsWorld.h"

#include "raylib.h"
#include <vector>

class Updatable;
class Game;
class TitleCard;

extern Game mainGameScene;

class Game
{
public:
	Game();
	Game(const Game& other) = delete;
	Game& operator= (const Game& other) = delete;
	~Game();

	void Update();

	void Register(Updatable* updatable);
	void KickCamera(Vector2 force);

	Camera2D camera;
	float cameraSize = 20.0f;
	float sceneTime = 0.0f;

	PhysicsWorld physicsWorld;

	bool paused;
	TitleCard* pauseCards[2] = { nullptr, nullptr };

	void SetPause(bool state);
	void Clear();

private:
	std::vector<Updatable*> updatableObjects;
	
	const float shakeFrequency = 300.0f;
	const float shakeDamping = 12.0f;
	Vector2 shakeVelocity = {0.0f, 0.0f};
	Vector2 shakeOffset = {0.0f, 0.0f};

	void SetupCamera();
};

void LoadNewGameScene();
void LoadTitleScene();