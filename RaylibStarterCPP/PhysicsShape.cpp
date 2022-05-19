
#include "PhysicsObject.h"
#include "PhysicsShape.h"
#include "raymath.h"
#include "raylibAdapter.h"

#include <limits>
#include <algorithm>

using std::max;
using std::min;

PhysicsShape::PhysicsShape(PhysicsObject* parent, Vector2* verticies, int vertexCount)
{
	this->parent = parent;
	offset = { 0.0f, 0.0f };

	this->verticies = new Vector2[vertexCount];
	for (int i = 0; i < vertexCount; i++)
	{
		this->verticies[i] = verticies[i];
	}
	this->vertexCount = vertexCount;
}

PhysicsShape::PhysicsShape(const PhysicsShape& other)
{
	parent = other.parent;
	offset = other.offset;

	verticies = new Vector2[other.vertexCount];
	for (int i = 0; i < other.vertexCount; i++)
	{
		verticies[i] = other.verticies[i];
	}
	vertexCount = other.vertexCount;
}

PhysicsShape& PhysicsShape::operator=(const PhysicsShape& other)
{
	parent = other.parent;
	offset = other.offset;

	verticies = new Vector2[other.vertexCount];
	for (int i = 0; i < other.vertexCount; i++)
	{
		verticies[i] = other.verticies[i];
	}
	vertexCount = other.vertexCount;

	return *this;
}

PhysicsShape::~PhysicsShape()
{
	delete[] verticies;
}

Vector2 ToWorld(Vector2 v, float rotation, Vector2 offset)
{
	return Vector2Rotate(v, rotation / PI * 180.0f) + offset;
}

bool Overlaps(PhysicsShape* a, PhysicsShape* b, CollisionData* outA, CollisionData* outB)
{
	if (a == nullptr) return false;
	if (b == nullptr) return false;

	if (a->vertexCount < 2) return false;
	if (b->vertexCount < 2) return false;

	float minOverlap = FLT_MAX;
	Vector2 normalA = { 0.0f, 0.0f };
	Vector2 normalB = { 0.0f, 0.0f };

	Vector2 offsetA = a->offset;
	float rotA = 0.0f;
	if (a->parent != nullptr)
	{
		rotA += a->parent->rotation;
		offsetA = Vector2Rotate(offsetA, rotA / PI * 180.0f);
		offsetA += a->parent->position;
	}

	Vector2 offsetB = b->offset;
	float rotB = 0.0f;
	if (b->parent != nullptr)
	{
		rotB += b->parent->rotation;
		offsetB = Vector2Rotate(offsetB, rotB / PI * 180.0f);
		offsetB += b->parent->position;
	}

	for (int i = 0; i < a->vertexCount + b->vertexCount; i++)
	{
		Vector2 normal;

		if (i < a->vertexCount)
		{
			Vector2 v1 = ToWorld(a->verticies[i], rotA, offsetA);
			Vector2 v2 = ToWorld(a->verticies[(i + 1) % a->vertexCount], rotA, offsetA);

			normal = Vector2Normalize(v1 - v2);
		}
		else
		{
			Vector2 v1 = ToWorld(b->verticies[i - a->vertexCount], rotB, offsetB);
			Vector2 v2 = ToWorld(b->verticies[(i - a->vertexCount + 1) % b->vertexCount], rotB, offsetB);

			normal = Vector2Normalize(v1 - v2);
		}

		normal = { normal.y, -normal.x };

		float aMax = -FLT_MAX;
		float aMin = FLT_MAX;

		for (int j = 0; j < a->vertexCount; j++)
		{
			Vector2 v = ToWorld(a->verticies[j], rotA, offsetA);

			float aProj = Vector2DotProduct(v, normal);
			aMax = max(aMax, aProj);
			aMin = min(aMin, aProj);
		}

		float bMax = -FLT_MAX;
		float bMin = FLT_MAX;

		for (int j = 0; j < b->vertexCount; j++)
		{
			Vector2 v = ToWorld(b->verticies[j], rotB, offsetB);

			float bProj = Vector2DotProduct(v, normal);
			bMax = max(bMax, bProj);
			bMin = min(bMin, bProj);
		}

		float overlap = min(aMax - bMin, bMax - aMin);
		if (overlap < 0)
		{
			return false;
		}

		if (overlap < minOverlap)
		{
			minOverlap = overlap;
			normalA = normal *(i < a->vertexCount ? 1.0f : -1.0f);
			normalB = normal * (i < a->vertexCount ? -1.0f : 1.0f);
		}
	}

	outA->normal = normalA;
	outA->overlap = minOverlap;
	outA->other = b;

	outB->normal = normalB;
	outB->overlap = minOverlap;
	outB->other = a;

	return true;
}