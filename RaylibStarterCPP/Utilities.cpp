
#include "Utilities.h"

float Utilities::Remap(float in, float oldMin, float oldMax, float newMin, float newMax)
{
	in -= oldMin;
	in /= (oldMax - oldMin);
	in *= (newMax - newMin);
	in += newMin;
	return in;
}

float Utilities::Sign(float in)
{
	return in > 0 ? 1.0f : -1.0f;
}

int Utilities::Sign(int in)
{
	return in > 0 ? 1 : -1;
}
