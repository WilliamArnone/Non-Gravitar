#pragma once

#include "objGame.h"
#include "Proiettile.h"
#include <vector>
#include <math.h>

class Torretta : public objGame
{
public:
	std::vector<Proiettile> list;
	int TimeToShoot;
	bool pro;
	Torretta();
	Torretta(float x, float y, float Angle);
	void Update(float fElapsedTime, float Px, float Py);
	~Torretta();
};

