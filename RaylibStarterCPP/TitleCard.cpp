
#include "raylib.h"
#include "raylibAdapter.h"
#include "TitleCard.h"
#include "Game.h"

TitleCard::TitleCard(string text, Vector2 offset, float size)
{
	this->text = text;
	this->offset = offset;
	this->size = size;
}

void TitleCard::DrawGUI()
{
	const float spacing = size / 10.0f;

	Vector2 textSize = MeasureTextEx(GetFontDefault(), text.c_str(), size, spacing);
	Vector2 screenDims = { GetScreenWidth(), GetScreenHeight()};
	DrawTextEx(GetFontDefault(), text.c_str(), Vector2{ 50.0f, (screenDims.y - textSize.y) / 2.0f } + offset, size, spacing, WHITE);
}

Clonable* TitleCard::Clone()
{
	TitleCard* gameOver = new TitleCard(text, offset, size);

	return gameOver;
}
