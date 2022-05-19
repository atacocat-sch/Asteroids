#pragma once

class Clonable
{
public:
	virtual Clonable* Clone() = 0;
};