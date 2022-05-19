#pragma once

#include "Clonable.h"

class Game;

class Updatable : public Clonable
{
public:
	Updatable();

	bool active = true;

	virtual void Update() {}
	virtual void Draw() {}
	virtual void DrawGUI() {}
};