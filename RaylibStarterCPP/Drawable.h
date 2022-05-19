#pragma once

#include "Clonable.h"

class Game;

class Drawable : public Clonable
{
public:
	Drawable();

	virtual void Draw() {}
};