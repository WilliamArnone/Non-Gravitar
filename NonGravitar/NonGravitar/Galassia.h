#pragma once
#include "Pianeta.h"
#include <iostream>
#include <ctime>
class Galassia
{
public:
	Galassia();
	Galassia(float screenwidth, float screenheight);
	int PlanetCollision(); //Galassia
	bool IsPointInsideCircle(float cx, float cy, float radius, float x, float y); //Galassia
	bool checkDistance(Pianeta pianeti[], int i, int c);
	~Galassia();
};

