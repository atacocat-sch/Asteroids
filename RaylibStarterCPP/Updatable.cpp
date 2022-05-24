
#include "Updatable.h"
#include "Game.h"

Updatable::Updatable()
{
	mainGameScene.Register(this);
}