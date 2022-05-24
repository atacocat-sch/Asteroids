
#include "Asteroid.h"
#include "Player.h"
#include "Bullet.h"
#include "Game.h"
#include "raymath.h"

void Bullet::Update()
{
	if (position.y > mainGameScene.cameraSize / 2.0f || position.y < mainGameScene.cameraSize / -2.0f)
	{
		active = false;
	}

	float sceneWidth = mainGameScene.cameraSize * ((float)GetScreenWidth() / GetScreenHeight());

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

	notPhysical = true;

	verts[0] = { 0.05f, 0.05f };
	verts[1] = { -0.05f, 0.05f };
	verts[2] = { -0.05f, -0.05f };
	verts[3] = { 0.05f, -0.05f };

	physicsShape = PhysicsShape(this, verts, 4);

	age = 0.0f;
}

void Bullet::OnCollision(CollisionData data)
{
	Asteroid* asteroid = dynamic_cast<Asteroid*>(data.other->parent);

	if (asteroid != nullptr)
	{
		asteroid->Split(Vector2Normalize(Vector2{velocity.y, -velocity.x}));
		if (parentPlayer != nullptr)
		{
			parentPlayer->points += parentPlayer->pointsPerAsteroid;
		}
	}

	active = false;
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