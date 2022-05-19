#pragma once

#include "raylib.h"

#include "Updatable.h"
#include "PhysicsObject.h"
#include "Bullet.h"

const int bulletPoolSize = 20;

class Player : public PhysicsObject
{
public:
	Player();

	const float moveSpeed = 15.0f;
	const float acceleration = 0.8f;

	const float turnSpeed = PI * 1;
	const float turnAcceleration = 6.0f;

	const float bulletSpeed = 25.0f;

	void Update();
	void Draw();
	void OnCollision(CollisionData data);


	Vector2 verticies[3];

	Clonable* Clone();
private:
	void ApplyMovement(float input);
	void ApplyTurning(float input);
	void Shoot(bool input);

	Bullet* bulletPool[bulletPoolSize];
};