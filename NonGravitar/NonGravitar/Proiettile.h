#pragma once

#include "objGame.h"

class Proiettile : public objGame
{
protected:
	int nSize;
	bool player = false;
	float x, y, dx, dy, angle;
public:
	Proiettile();
	void Update(float fElapsedTime);
	bool IsOutOfMap(float width, float heigth);
	~Proiettile();
};
