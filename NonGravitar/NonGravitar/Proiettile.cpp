#include "Proiettile.h"

Proiettile::Proiettile()
{
}

Proiettile::~Proiettile()
{
}
Proiettile::Proiettile(bool p, float x, float y, float a) {
	player = p;
	X = x;
	Y = y;
	angle = a;
	dx = 0;
	dy = 0;
}

void Proiettile::Update(float fElapsedTime) {
	dx = dx * fElapsedTime;
	dy = dy * fElapsedTime;
	angle -= 1.0f * fElapsedTime;
}

bool Proiettile::IsOutOfMap(float width, float heigth) {
	if (X < 1 || Y < 1 || X >= width - 1 || Y >= heigth - 1)
		return true;
}