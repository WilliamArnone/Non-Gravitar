#pragma once

#include <iostream>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <string>
#include <math.h>

#include "Proiettile.h"
#include "objGame.h"

class Navicella : public objGame
{
protected:
	float x1, y1;
	float x2, y2;
	float angle;
	int life, fuel;
public:
	Navicella();
	void setShip(float width, float heigth);
	void ShipMove(float fElapsedTime, bool Up);
	void ShipRotate(float fElapsedTime, bool Left);
	~Navicella();
};

