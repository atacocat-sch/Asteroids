#pragma once

#include "raylib.h"

#include "Updatable.h"
#include "PhysicsObject.h"
#include "Bullet.h"

const int bulletPoolSize = 20;
const int playerVertexCount = 3;

class Player : public PhysicsObject
{
public:
	Player();

	const float moveSpeed = 15.0f;
	const float acceleration = 0.8f;

	const float turnSpeed = PI * 1.0f;
	const float turnAcceleration = 18.0f;

	const float bulletSpeed = 25.0f;

	int points = 0;
	const int pointsPerAsteroid = 100;

	int lives = 3;
	float invincibility = 0.0f;

	void Update();
	void Draw();
	void DrawGUI();
	void OnCollision(CollisionData data);

	Vector2 verticies[playerVertexCount];

	Clonable* Clone();
private:
	void ApplyMovement(float input);
	void ApplyTurning(float input);
	void Shoot(bool input);
	void CalcEdgeCollision();

	Bullet* bulletPool[bulletPoolSize];
};