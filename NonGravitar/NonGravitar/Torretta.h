#pragma once

#include "objGame.h"
#include <math.h>

class Torretta : public objGame
{
protected:
	float XUp, YUp;
	int TimeToShoot;
public:
	float Xl, Xr;
	float Yl, Yr;
	Torretta();
	Torretta(float width, float heigth);
	void Update(float fElapsedTime, float Px, float Py);
	~Torretta();
};

