#pragma once

#include "PhysicsObject.h"

class Bullet : public PhysicsObject
{
public:
	float age;

	void Update();
	void Draw();
	void Reset();

	Clonable* Clone();
};