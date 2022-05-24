
#include "raylibTools.h"

Vector2 Vector2Reflect(Vector2 in, Vector2 normal)
{
    Vector2 result = { 0 };

    float dotProduct = (in.x * normal.x + in.y * normal.y); // Dot product

    result.x = in.x - (2.0f * normal.x) * dotProduct;
    result.y = in.y - (2.0f * normal.y) * dotProduct;

    return result;
}