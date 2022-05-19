
#include "Bullet.h"
#include "Game.h"

void Bullet::Update()
{
	if (position.y > mainGameScene->cameraSize / 2.0f || position.y < mainGameScene->cameraSize / -2.0f)
	{
		active = false;
	}

	float sceneWidth = mainGameScene->cameraSize * ((float)GetScreenWidth() / GetScreenHeight());

	if (position.x > sceneWidth / 2.0f || position.x < sceneWidth / -2.0f)
	{
		active = false;
	}

	age += GetFrameTime();
}

void Bullet::Draw()
{
	DrawCircleV(position, 0.05f, WHITE);
}

void Bullet::Reset()
{
	active = true;

	position = { 0.0f, 0.0f };
	velocity = {0.0f, 0.0f};

	rotation = 0.0f;
	angularVelocity = 0.0f;

	age = 0.0f;
}

Clonable* Bullet::Clone()
{
	Bullet* clone = new Bullet();

	clone->position = position;
	clone->velocity = velocity;

	clone->rotation = rotation;
	clone->angularVelocity = angularVelocity;

	return clone;
}