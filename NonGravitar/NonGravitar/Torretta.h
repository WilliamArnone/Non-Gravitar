#pragma once

#include <vector>
#include "Proiettile.h"


class Torretta : objGame
{
public:
	Torretta();

	int TimeToShoot;
	Proiettile Shoot();	//override per la figlia che mira alla navicella

	~Torretta();
};

