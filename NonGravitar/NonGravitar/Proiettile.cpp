#include "Proiettile.h"
#include <math.h>

Proiettile::Proiettile()
{
}

Proiettile::~Proiettile()
{
}

//Secondo costruttore del proiettile
Proiettile::Proiettile(bool p, float x, float y, float a) {
	player = p;
	X = x;
	Y = y;
	angle = 100.0f;
	dx = 50.0f * sinf(a);
	dy = -50.0f * cosf(a);
	Size = 1;
}

//Update del proiettile, modificando la direzione e l'angolo
void Proiettile::Update(float fElapsedTime) {
	X += dx * fElapsedTime;
	Y += dy * fElapsedTime;
	angle -= 1.0f * fElapsedTime;
}