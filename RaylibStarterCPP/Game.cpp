
#include "raylib.h"

#include "Game.h"
#include "Updatable.h"

#include <iostream>

Game* mainGameScene;
void SetupCamera(Camera2D* camera, float cameraSize);

Game::Game()
{
	mainGameScene = this;
	SetupCamera(&camera, cameraSize);
}

Game& Game::operator= (const Game& other)
{
	if (&other == this)
	{
		return *this;
	}

	cameraSize = other.cameraSize;

	for (Updatable* updatable : updatableObjects)
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
	if (!IsKeyDown(KEY_INSERT) || IsKeyPressed(KEY_HOME))
	{
		SetupCamera(&camera, cameraSize);

		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode2D(camera);

		physicsWorld.Update();

		for (Updatable* updatable : updatableObjects)
		{
			if (updatable->active)
			{
				updatable->Update();
			}
		}

		/*BeginDrawing();
		ClearBackground(BLACK);
		BeginMode2D(camera);*/

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
	}
	else
	{
		BeginDrawing();
		EndDrawing();
	}
}

void Game::Register(Updatable* updatable)
{
	updatableObjects.push_back(updatable);
}

void SetupCamera(Camera2D* camera, float cameraSize)
{
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	float zoom = screenHeight / cameraSize;

	*camera = { {screenWidth / 2.0f, screenHeight / 2.0f}, {0.0f, 0.0f}, 0.0f, zoom };
}