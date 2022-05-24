#pragma once

#include "PhysicsShape.h"
#include "Updatable.h"
#include "raylib.h"

class PhysicsObject : public Updatable
{
public:
	PhysicsObject();

	Vector2 position = { 0.0f, 0.0f };
	Vector2 velocity = { 0.0f, 0.0f };

	float rotation = 0.0f;
	float angularVelocity = 0.0f;

	float mass = 1.0f;

	bool notPhysical = false;

	PhysicsShape physicsShape = {this, nullptr, 0};
	
	virtual void OnCollision(CollisionData data) {}
};