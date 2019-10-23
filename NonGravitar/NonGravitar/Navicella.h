#pragma once

#include <iostream>
#include <algorithm>
#include <ctime>
#include <string>
#include <math.h>
#include "objGame.h"

class Navicella : public objGame
{
public:
	float dx, dy;
	int fuel;
	Navicella();
	void ShipMove(float fElapsedTime, bool Up);
	void ShipRotate(float fElapsedTime, bool Left);
	~Navicella();
};

