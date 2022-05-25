
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

Game::~Game()
{
	Clear();
}

void Game::Update()
{
	float deltaTime = GetFrameTime();

	shakeVelocity -= shakeOffset * shakeFrequency * deltaTime;
	shakeVelocity -= shakeVelocity * shakeDamping * deltaTime;
	shakeOffset += shakeVelocity * deltaTime;

	SetupCamera();

	if (!paused)
	{
		physicsWorld.Update();
	}

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

	if (IsKeyPressed(KEY_ESCAPE))
	{
		if (!paused)
		{
			SetPause(true);
		}
		else
		{
			LoadTitleScene();
		}
	}

	if (IsKeyPressed(KEY_ENTER) && paused)
	{
		SetPause(false);
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

void Game::SetPause(bool state)
{
	paused = state;

	pauseCards[0]->active = state;
	pauseCards[1]->active = state;
}

void Game::Clear()
{
	physicsWorld = PhysicsWorld();

	for (int i = 0; i < updatableObjects.size(); i++)
	{
		delete updatableObjects[i];
	}

	updatableObjects.clear();
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
	mainGameScene.Clear();

	new Player();
	new AsteroidPool();

	mainGameScene.pauseCards[0] = new TitleCard(string("Paused"), { 0.0f, 0.0f }, 64.0f);
	mainGameScene.pauseCards[1] = new TitleCard(string("Press ENTER to Continue\nPress ESCAPE to Quit"), { 0.0f, 160.0f }, 22.0f);

	mainGameScene.pauseCards[0]->active = false;
	mainGameScene.pauseCards[1]->active = false;

	SetExitKey(0);
}

void LoadTitleScene()
{
	forceStop = true;
	mainGameScene.Clear();

	new TitleCard(string("Definitely not just\na blatant rip-off of the hit\n1980's game Asteroids"), {0.0f, 0.0f}, 64.0f);
	new TitleCard(string("Press ENTER to Start"), {0.0f, 160.0f}, 22.0f);
	new TitleCard(string("Press GRAVE to achieve nothing"), {0.0f, 195.0f}, 22.0f);
	new TitleCard(string("Press ESCAPE to Quit"), {0.0f, 230.0f}, 22.0f);

	new KeyAction(KEY_ENTER, LoadNewGameScene);
	SetExitKey(KEY_ESCAPE);

	AsteroidPool* asteroidPool = new AsteroidPool();
}
