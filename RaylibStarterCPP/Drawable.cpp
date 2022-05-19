
#include "Drawable.h"
#include "Game.h"

Drawable::Drawable()
{
	mainGameScene->Register(this);
}