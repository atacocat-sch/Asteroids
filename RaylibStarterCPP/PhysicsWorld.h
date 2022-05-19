#pragma once

#include "Updatable.h"
#include <vector>

class PhysicsObject;

const int maxPhysicsObjects = 100;

class PhysicsWorld
{
public:
	PhysicsWorld();

	void Update();
	void Register(PhysicsObject* newObject);
	void Unregister(PhysicsObject* oldObject);

private:
	PhysicsObject* physicsObjects[maxPhysicsObjects];

	void ApplyMovement();
	void CheckCollision();
};