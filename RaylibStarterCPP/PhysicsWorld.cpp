
#include "PhysicsWorld.h"
#include "PhysicsObject.h"
#include "raylib.h"
#include "raylibTools.h"
#include "raylibAdapter.h"
#include "Game.h"

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
						Vector2 aVelocity = a->velocity;
						Vector2 bVelocity = b->velocity;

						bool physicalCollision = !a->notPhysical && !b->notPhysical;

						if (physicalCollision)
						{
							a->position += dataA.normal * dataA.overlap;
							b->position += dataB.normal * dataB.overlap;

							Vector2 normal = dataA.normal;
							Vector2 tangent = { normal.y, -normal.x };

							float tangentDotA = Vector2DotProduct(aVelocity, tangent);
							float tangentDotB = Vector2DotProduct(bVelocity, tangent);

							float normalDotA = Vector2DotProduct(aVelocity, normal);
							float normalDotB = Vector2DotProduct(bVelocity, normal);

						 	float mA = normalDotA* (a->mass - b->mass) / (a->mass + b->mass) + normalDotB * (2.0f * b->mass) / (a->mass + b->mass);
							float mB = normalDotA* (2.0f * a->mass) / (a->mass + b->mass) + normalDotB * (b->mass - a->mass) / (a->mass + b->mass);

							a->velocity = tangent * tangentDotA + normal * mA;
							b->velocity = tangent * tangentDotB + normal * mB;
						}

						a->OnCollision(dataA);
						b->OnCollision(dataB);

						mainGameScene.KickCamera((a->velocity * a->mass + b->velocity * b->mass) * 0.1f);
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
