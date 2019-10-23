#pragma once

#include "objGame.h"

class Carburante : public objGame
{
public:
	float liter;
	bool pro;
	Carburante();
	Carburante(float x, float y);
	~Carburante();
};

