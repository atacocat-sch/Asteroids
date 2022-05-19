#pragma once

#include "raylib.h";

struct Vector2;

class PhysicsObject;
class PhysicsShape;

struct CollisionData
{
	PhysicsShape* other;
	Vector2 normal;
	float overlap;
};

class PhysicsShape
{
public:
	PhysicsShape(PhysicsObject* parent, Vector2* verticies, int vertexCount);
	PhysicsShape(const PhysicsShape& other);
	PhysicsShape& operator=(const PhysicsShape& other);
	~PhysicsShape();

	PhysicsObject* parent;
	Vector2 offset = {0.0f, 0.0f};

	Vector2* verticies = nullptr;
	int vertexCount = 0;
};

bool Overlaps(PhysicsShape* a, PhysicsShape* b, CollisionData* outA, CollisionData* outB);