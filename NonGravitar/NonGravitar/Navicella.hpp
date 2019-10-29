#pragma once

#include <iostream>
#include <algorithm>
#include <ctime>
#include <string>
#include <math.h>
#include "objGame.hpp"

class Navicella : public objGame
{
public:
	//punti per la direzione e velocità della navicella
	float dx, dy; 
	//carburante disponibile
	int fuel;
	Navicella();
	void ShipMove(float fElapsedTime, bool Up);
	void ShipRotate(float fElapsedTime, bool Left);
	~Navicella();
};

