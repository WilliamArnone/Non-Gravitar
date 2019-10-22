#pragma once

#include "objGame.h"

class Carburante : public objGame
{
public:
	float r, liter;
	Carburante();
	Carburante(float x, float y);
	~Carburante();
};

