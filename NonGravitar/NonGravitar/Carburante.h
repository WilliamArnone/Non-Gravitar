#pragma once

#include "objGame.h"

class Carburante : objGame
{
private:
	float xc;
	float yc;
	float r;
	int type;
	bool IsHere = false;
	bool taken = false;
public:

	Carburante();
	~Carburante();
};

