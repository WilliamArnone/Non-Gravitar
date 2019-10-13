#include "Proiettile.h"

Proiettile::Proiettile()
{
}

Proiettile::~Proiettile()
{
}

void Proiettile::Update(float fElapsedTime) {
	x += dx * fElapsedTime;
	y += dy * fElapsedTime;
	angle -= 1.0f * fElapsedTime;
}

bool Proiettile::IsOutOfMap(float width, float heigth) {
	if (x < 1 || y < 1 || x >= width - 1 || y >= heigth - 1)
		return true;
}