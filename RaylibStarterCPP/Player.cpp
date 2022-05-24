#include "Game.h"
#include "Player.h"
#include "raylib.h"
#include "raylibTools.h"
#include "raymath.h"
#include "raylibAdapter.h"
#include "Asteroid.h"
#include "TitleCard.h"

#include <cmath>
#include <iostream>
#include <string>

using std::sin;
using std::cos;

Player::Player()
{
	for (int i = 0; i < bulletPoolSize; i++)
	{
		bulletPool[i] = new Bullet();
		bulletPool[i]->active = false;
		bulletPool[i]->parentPlayer = this;
	}

	mass = 10.0f;

	verticies[0] = { 0.5f, 0.0f };
	verticies[1] = FromPolarDeg(140.0f, 0.5f);
	verticies[2] = FromPolarDeg(220.0f, 0.5f);

	physicsShape = PhysicsShape(this, verticies, 4);
}

Clonable* Player::Clone()
{
	Player* player = new Player();

	player->position = position;
	player->velocity = velocity;

	player->rotation = rotation;

	return (Updatable*)player;
}

void GetInput(float* moveInput, float* turnInput, bool* shootInput)
{
	if (moveInput != nullptr)
	{
		if (IsKeyDown(KEY_W)) (*moveInput) += 1;
		if (IsKeyDown(KEY_S)) (*moveInput) -= 1;
	}

	if (turnInput != nullptr)
	{
		if (IsKeyDown(KEY_D)) (*turnInput) += 1;
		if (IsKeyDown(KEY_A)) (*turnInput) -= 1;
	}

	if (shootInput != nullptr)
	{
		if (IsKeyPressed(KEY_SPACE)) (*shootInput) = true;
	}
}

void Player::Update()
{
	float moveInput = 0.0f;
	float turnInput = 0.0f;
	bool shootInput = false;

	GetInput(&moveInput, &turnInput, &shootInput);

	ApplyMovement(moveInput);
	ApplyTurning(turnInput);
	Shoot(shootInput);

	CalcEdgeCollision();

	if (IsKeyPressed(KEY_MINUS))
	{
		lives = 0;
		new TitleCard(string("Game Over"), { 0.0f, 0.0f }, 72.0f);
		new TitleCard(string("Press Space to Continue"), { 0.0f, 60.0f }, 18.0f);
		active = false;
	}

	invincibility -= GetFrameTime();
}

void Player::ApplyMovement(float input)
{
	Vector2 forward = { cos(rotation), sin(rotation) };

	Vector2 target = forward * input * moveSpeed;
	Vector2 difference = target - velocity;
	Vector2 force = difference * acceleration;

	velocity += force * GetFrameTime();
}

void Player::ApplyTurning(float input)
{
	float target = input * turnSpeed;
	float difference = target - angularVelocity;
	float torque = difference * turnAcceleration;

	angularVelocity += torque * GetFrameTime();
}

void Player::Shoot(bool input)
{
	if (input)
	{
		Bullet* bullet = nullptr;
		for (int i = 0; i < bulletPoolSize; i++)
		{
			if (!bulletPool[i]->active)
			{
				bullet = bulletPool[i];
				break;
			}
		}

		if (bullet == nullptr)
		{
			bullet = bulletPool[0];
			for (int i = 1; i < bulletPoolSize; i++)
			{
				if (bulletPool[i]->age > bullet->age)
				{
					bullet = bulletPool[i];
				}
			}
		}

		Vector2 forward = { cos(rotation), sin(rotation) };

		bullet->Reset();
		bullet->position = position + forward;
		bullet->velocity = forward * bulletSpeed;
	}
}

void Player::CalcEdgeCollision()
{
	float halfScreenHeight = mainGameScene.cameraSize / 2.0f;
	float halfScreenWidth = halfScreenHeight * ((float)GetScreenWidth() / GetScreenHeight());
	float rotDeg = rotation / PI * 180.0f;

	for (int i = 0; i < playerVertexCount; i++)
	{
		Vector2 v = Vector2Rotate(verticies[i], rotDeg) + position;
		bool hasCollision = false;

		if (v.x > halfScreenWidth || v.x < -halfScreenWidth)
		{
			velocity = Vector2Reflect(velocity, { 1.0f, 0.0f });
			hasCollision = true;
		}

		if (v.y > halfScreenHeight || v.y < -halfScreenHeight)
		{
			velocity = Vector2Reflect(velocity, { 0.0f, 1.0f });
			hasCollision = true;
		}

		if (hasCollision)
		{
			return;
		}
	}
}

void Player::Draw()
{
	float rotDeg = rotation / PI * 180.0f;

	float flashTime = GetTime() * 15.0f;
	if (invincibility <= 0.0f || flashTime - (int)flashTime > 0.5)
	{
		DrawLineV(position + Vector2Rotate(Vector2{ 0.5f, 0.0f }, rotDeg), position + FromPolarDeg(140.0f + rotDeg, 0.5f), WHITE);
		DrawLineV(position + Vector2Rotate(Vector2{ 0.5f, 0.0f }, rotDeg), position + FromPolarDeg(220.0f + rotDeg, 0.5f), WHITE);
		DrawLineV(position + Vector2Rotate(Vector2{ -0.1f, 0.0f }, rotDeg), position + FromPolarDeg(140.0f + rotDeg, 0.5f), WHITE);
		DrawLineV(position + Vector2Rotate(Vector2{ -0.1f, 0.0f }, rotDeg), position + FromPolarDeg(220.0f + rotDeg, 0.5f), WHITE);
	}

	float moveInput = 0.0f;
	GetInput(&moveInput, nullptr, nullptr);

	if (flashTime - (int)flashTime > 0.5f && abs(moveInput) > 0.01f)
	{
		DrawLineV(position + Vector2Rotate(Vector2{ -0.5f, 0.0f }, rotDeg), position + Vector2Rotate(Vector2{ -0.1f, 0.0f }, rotDeg) + FromPolarDeg(140.0f + rotDeg, 0.3f), WHITE);
		DrawLineV(position + Vector2Rotate(Vector2{ -0.5f, 0.0f }, rotDeg), position + Vector2Rotate(Vector2{ -0.1f, 0.0f }, rotDeg) + FromPolarDeg(220.0f + rotDeg, 0.3f), WHITE);
	}
}

void Player::DrawGUI()
{
	using std::string;
	using std::to_string;

	DrawText((to_string(points) + " pts").c_str(), 20, 20, 32, WHITE);

	int sw = GetScreenWidth();
	int sh = GetScreenHeight();

	for (int i = 0; i < lives; i++)
	{
		int offset = i * 30;
		DrawLine(sw - 20 - offset, 20, sw - 12 - offset, 40, WHITE);
		DrawLine(sw - 20 - offset, 20, sw - 28 - offset, 40, WHITE);

		DrawLine(sw - 12 - offset, 40, sw - 20 - offset, 35, WHITE);
		DrawLine(sw - 28 - offset, 40, sw - 20 - offset, 35, WHITE);
	}
}

void Player::OnCollision(CollisionData data)
{
	Asteroid* asteroid = dynamic_cast<Asteroid*>(data.other->parent);

	if (asteroid != nullptr && invincibility <= 0.0f)
	{
		lives--;
		invincibility = 1.5f;
		if (lives == 0)
		{
			new TitleCard(string("Game Over"), { 0.0f, 0.0f }, 72.0f);
			new TitleCard(string("Press Space to Continue"), { 0.0f, 60.0f }, 18.0f);
			active = false;
		}
	}
}
