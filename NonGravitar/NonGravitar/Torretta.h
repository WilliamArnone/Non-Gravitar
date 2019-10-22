#pragma once

#include "objGame.h"
#include <math.h>

class Torretta : public objGame
{
public:
	int TimeToShoot;
	bool pro;
	float XUp, YUp;
	float Xl, Xr;
	float Yl, Yr;
	Torretta();
	Torretta(float xu, float yu, float xl, float yl, float xr, float yr);
	void Update(float fElapsedTime, float Px, float Py);
	~Torretta();
};

