#include "Game.h"
#include "Player.h"
#include "raylib.h"
#include "raymath.h"
#include "raylibAdapter.h"

#include <cmath>
#include <iostream>

using std::sin;
using std::cos;

Player::Player()
{
	for (int i = 0; i < bulletPoolSize; i++)
	{
		bulletPool[i] = new Bullet();
		bulletPool[i]->active = false;
	}

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
	if (IsKeyDown(KEY_W)) (*moveInput) += 1;
	if (IsKeyDown(KEY_S)) (*moveInput) -= 1;

	if (IsKeyDown(KEY_D)) (*turnInput) += 1;
	if (IsKeyDown(KEY_A)) (*turnInput) -= 1;

	if (IsKeyPressed(KEY_SPACE)) (*shootInput) = true;
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

void Player::Draw()
{
	float rotDeg = rotation / PI * 180.0f;

	DrawLineV(position + Vector2Rotate(Vector2{ 0.5f, 0.0f }, rotDeg), position + Vector2Rotate(FromPolarDeg(140.0f, 0.5f), rotDeg), WHITE);
	DrawLineV(position + Vector2Rotate(Vector2{ 0.5f, 0.0f }, rotDeg), position + Vector2Rotate(FromPolarDeg(220.0f, 0.5f), rotDeg), WHITE);
	DrawLineV(position + Vector2Rotate(Vector2{ -0.1f, 0.0f }, rotDeg), position + Vector2Rotate(FromPolarDeg(140.0f, 0.5f), rotDeg), WHITE);
	DrawLineV(position + Vector2Rotate(Vector2{ -0.1f, 0.0f }, rotDeg), position + Vector2Rotate(FromPolarDeg(220.0f, 0.5f), rotDeg), WHITE);
}

void Player::OnCollision(CollisionData data)
{

}
