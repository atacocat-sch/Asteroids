
#include "raylib.h"
#include "raylibAdapter.h"

#include "Game.h"
#include "Updatable.h"

#include "Player.h"
#include "AsteroidPool.h"
#include "TitleCard.h"
#include "KeyAction.h"

#include <iostream>

Game mainGameScene;
bool forceStop = false;

Game::Game()
{
	SetupCamera();
}

Game& Game::operator= (const Game& other)
{
	if (&other == this)
	{
		return *this;
	}

	cameraSize = other.cameraSize;

	for (int i = 0; i < updatableObjects.size(); i++)
	{
		delete updatableObjects[i];
	}
	updatableObjects.clear();

	physicsWorld = PhysicsWorld();

	for (Updatable* updatable : other.updatableObjects)
	{
		updatableObjects.push_back((Updatable*)updatable->Clone());
	}
}

Game::~Game()
{
	for (int i = 0; i < updatableObjects.size(); i++)
	{
		delete updatableObjects[i];
	}

	updatableObjects.clear();
}

void Game::Update()
{
	float deltaTime = GetFrameTime();

	shakeVelocity -= shakeOffset * shakeFrequency * deltaTime;
	shakeVelocity -= shakeVelocity * shakeDamping * deltaTime;
	shakeOffset += shakeVelocity * deltaTime;

	SetupCamera();

	physicsWorld.Update();

	for (Updatable* updatable : updatableObjects)
	{
		if (updatable->active)
		{
			updatable->Update();
			if (forceStop)
			{
				forceStop = false;
				return;
			}
		}
	}

	BeginDrawing();
	ClearBackground(BLACK);
	BeginMode2D(camera);

	for (Updatable* updatable : updatableObjects)
	{
		if (updatable->active)
		{
			updatable->Draw();
		}
	}

	EndMode2D();

	for (Updatable* updatable : updatableObjects)
	{
		if (updatable->active)
		{
			updatable->DrawGUI();
		}
	}

	EndDrawing();

	sceneTime += deltaTime;
}

void Game::Register(Updatable* updatable)
{
	updatableObjects.push_back(updatable);
}

void Game::KickCamera(Vector2 force)
{
	shakeVelocity += force;
}

void Game::SetupCamera()
{
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	float zoom = screenHeight / cameraSize;

	camera = { {screenWidth / 2.0f, screenHeight / 2.0f}, shakeOffset, 0.0f, zoom };
}

void LoadNewGameScene()
{
	forceStop = true;
	mainGameScene = Game();

	new Player();
	new AsteroidPool();

	new KeyAction(KEY_ESCAPE, LoadTitleScene);
	SetExitKey(0);
}

void LoadTitleScene()
{
	forceStop = true;
	mainGameScene = Game();

	new TitleCard(string("Definitely not just\na blatant rip-off of the hit\n1980's game Asteroids"), {0.0f, 0.0f}, 64.0f);
	new TitleCard(string("Press ENTER to Start"), {0.0f, 160.0f}, 22.0f);
	new TitleCard(string("Press GRAVE to achieve nothing"), {0.0f, 195.0f}, 22.0f);
	new TitleCard(string("Press ESCAPE to Quit"), {0.0f, 230.0f}, 22.0f);

	new KeyAction(KEY_ENTER, LoadNewGameScene);
	SetExitKey(KEY_ESCAPE);

	AsteroidPool* asteroidPool = new AsteroidPool();
}
