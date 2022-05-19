
#include "PhysicsObject.h"
#include "PhysicsShape.h"

#include "Game.h"

PhysicsObject::PhysicsObject()
{
	mainGameScene->physicsWorld.Register(this);
}