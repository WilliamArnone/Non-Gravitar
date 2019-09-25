#pragma once

#include "objGame.h"
#include "olcConsoleGameEngine.h"

class Navicella : public objGame
{
protected: 
	float x1, y1;
	float x2, y2;
	float angle;
	int life, fuel;
public:
	Navicella();
	void setShip();
	void ShipMove(float fElapsedTime, olcConsoleGameEngine::sKeyState keyboard[]);
	~Navicella();
};

