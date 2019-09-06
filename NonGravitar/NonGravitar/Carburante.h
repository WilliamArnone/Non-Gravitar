#pragma once

#include "objGame.h"

class Carburante : public objGame
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

	int color;
	int litri;

	~Carburante();
};

