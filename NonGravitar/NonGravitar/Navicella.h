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
public:
	int fuel;
	float dx, dy;
	void ShipMove(float fElapsedTime, bool Up);
	void ShipRotate(float fElapsedTime, bool Left);
	Navicella();
	void setShip();
	~Navicella();
};

