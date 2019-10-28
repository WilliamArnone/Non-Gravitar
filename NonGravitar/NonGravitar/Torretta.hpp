#pragma once

#include "objGame.hpp"
#include "Proiettile.hpp"
#include <vector>
#include <math.h>

class Torretta : public objGame
{
public:
	std::vector<Proiettile> TorreProiettili;
	int TimeToShoot;
	bool pro;
	Torretta();
	Torretta(float x, float y, float Angle);
	void Update(float fElapsedTime, float Px, float Py);
	~Torretta();
};

