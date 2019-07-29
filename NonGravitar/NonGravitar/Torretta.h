#pragma once

#include "objGame.h"

class Torretta : objGame
{
public:
	Torretta();

	int TimeToShoot;
	vector<Proiettile> Shoot();	//override per la figlia che mira alla navicella

	~Torretta();
};

