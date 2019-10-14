#pragma once

#include <vector>
#include "Proiettile.h"


class Torretta : public objGame
{
protected:
	float x1, x2, x3;
	float y1, y2, y3;
	int TimeToShoot;
public:
	Torretta();
	void Update(float fElapsedTime);
	//Proiettile Shoot();
	~Torretta();
};

