#pragma once

#include "Updatable.h"

class KeyAction : public Updatable
{
public:
	KeyAction(int key, void (*callback)());

	void (*keyDownCallback)() = nullptr;
	int key = -1;

	void Update();

	Clonable* Clone();
};