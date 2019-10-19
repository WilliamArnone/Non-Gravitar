#pragma once

#include "objGame.h"

class Carburante : public objGame
{
private:
	float r, liter;
public:
	Carburante();
	Carburante(float x, float y);
	~Carburante();
};

