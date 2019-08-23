#pragma once

#include "objGame.h"

class Proiettile : objGame
{
protected:
	int nSize;
	float x;
	float y;
	float dx;
	float dy;
	float angle;
	bool player = false;
public:
	Proiettile();
	~Proiettile();
};

