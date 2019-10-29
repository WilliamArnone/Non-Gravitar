#include "Proiettile.hpp"
#include <math.h>

Proiettile::Proiettile()
{
}

Proiettile::~Proiettile()
{
}
Proiettile::Proiettile(bool p, float x, float y, float a): objGame(x,y,1) {
	player = p;
	angle = a;
	Color = p ? 15 : 4;
}


void Proiettile::Update(float fElapsedTime) {
	//viene aggiornata la posizione del proiettile 
	X += 80.0f * sinf(angle) * fElapsedTime;
	Y += -80.0f * cosf(angle) * fElapsedTime;
}