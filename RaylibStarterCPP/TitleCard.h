#pragma once

#include "Updatable.h"
#include <string>

using std::string;

class TitleCard : public Updatable
{
public:
	string text;
	Vector2 offset;
	float size;

	TitleCard(string text, Vector2 offset, float size);

	void DrawGUI();

	Clonable* Clone();
};