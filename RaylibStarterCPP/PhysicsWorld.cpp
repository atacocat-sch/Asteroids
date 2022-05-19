
#include "PhysicsWorld.h"
#include "PhysicsObject.h"
#include "raylib.h"
#include "raylibAdapter.h"

#include <iostream>
#include <algorithm>

using std::min;
using std::max;

PhysicsWorld::PhysicsWorld()
{
	for (int i = 0; i < maxPhysicsObjects; i++)
	{
		physicsObjects[i] = nullptr;
	}
}

void PhysicsWorld::Update()
{
	ApplyMovement();
	CheckCollision();

}

void PhysicsWorld::ApplyMovement()
{
	float deltaTime = GetFrameTime();
	for (int i = 0; i < maxPhysicsObjects; i++)
	{
		PhysicsObject* physicsObject = physicsObjects[i];

		if (physicsObject != nullptr)
		{
			physicsObject->position += physicsObject->velocity * deltaTime;
			physicsObject->rotation += physicsObject->angularVelocity * deltaTime;
		}
	}
}

void PhysicsWorld::CheckCollision()
{
	for (int i = 0; i < maxPhysicsObjects; i++)
	{
		for (int j = i + 1; j < maxPhysicsObjects; j++)
		{
			PhysicsObject* a = physicsObjects[i];
			PhysicsObject* b = physicsObjects[j];

			if (a != nullptr && b != nullptr)
			{
				CollisionData dataA;
				CollisionData dataB;

				if (a->active && b->active)
				{
					if (Overlaps(&a->physicsShape, &b->physicsShape, &dataA, &dataB))
					{
						Vector2 netForce = a->velocity + b->velocity;
						float totalMass = a->mass + b->mass;

						a->position += dataA.normal * dataA.overlap;
						if (Vector2Length(a->velocity) > 0.001f)
						{
							a->velocity += Vector2Normalize(a->velocity) * min(Vector2DotProduct(a->velocity, dataA.normal), 0.0f);
						}
						a->OnCollision(dataA);

						b->position += dataB.normal * dataB.overlap;
						if (Vector2Length(b->velocity) > 0.001f)
						{
							b->velocity += Vector2Normalize(b->velocity) * min(Vector2DotProduct(b->velocity, dataB.normal), 0.0f);
						}
						b->OnCollision(dataB);
					}
				}
			}
		}
	}
}

void PhysicsWorld::Register(PhysicsObject* newObject)
{
	for (int i = 0; i < maxPhysicsObjects; i++)
	{
		if (physicsObjects[i] == nullptr)
		{
			physicsObjects[i] = newObject;
			return;
		}
	}
}

void PhysicsWorld::Unregister(PhysicsObject* oldObject)
{
	for (int i = 0; i < maxPhysicsObjects; i++)
	{
		if (physicsObjects[i] == oldObject)
		{
			physicsObjects[i] = nullptr;
			return;
		}
	}
}
