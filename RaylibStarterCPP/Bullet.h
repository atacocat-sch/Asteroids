#pragma once

#include "PhysicsObject.h"

class Player;

class Bullet : public PhysicsObject
{
public:
	Player* parentPlayer;

	float age;

	void Update();
	void Draw();
	void Reset();
	void OnCollision(CollisionData data);

	Vector2 verts[4];

	Clonable* Clone();
};