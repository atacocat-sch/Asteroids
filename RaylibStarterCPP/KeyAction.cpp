
#include "KeyAction.h"
#include "raylib.h"

KeyAction::KeyAction(int key, void(*callback)())
{
	this->key = key;
	keyDownCallback = callback;
}

void KeyAction::Update()
{
	if (key != -1)
	{
		if (IsKeyPressed(key) && keyDownCallback != nullptr)
		{
			keyDownCallback();
		}
	}
}

Clonable* KeyAction::Clone()
{
	return new KeyAction(key, keyDownCallback);
}