#pragma once

#include "objGame.h"

class Carburante : public objGame
{
private:
	float xc, yc, r;
	int type;
	bool IsHere = false;
	bool taken = false;
public:

	Carburante();
	~Carburante();
};

