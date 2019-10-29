#pragma once

#include "objGame.hpp"
#include "Proiettile.hpp"
#include <vector>
#include <math.h>

class Torretta : public objGame
{
public:
	//vettore di proiettili sparati dalla torretta 
	std::vector<Proiettile> TorreProiettili;
	//valore che scandisce lo sparo della torretta 
	int TimeToShoot;
	//identifica il tipo di torretta
	bool pro;
	Torretta();
	Torretta(float x, float y, float Angle);
	void Update(float fElapsedTime, float Px, float Py);
	~Torretta();
};

