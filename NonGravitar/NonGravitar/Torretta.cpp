#include "Torretta.h"

Torretta::Torretta()
{
}

Torretta::Torretta(float width, float heigth)
{
	TimeToShoot = 500;
	X = width;
	Y = heigth;
	XUp = X;
	YUp = Y + 2;
	Xl = X - 2;
	Xr = X + 2;
}

void Torretta::Update(float fElapsedTime, float Px, float Py) {
	angle = atan2f(Px - X, Y - Py);
	TimeToShoot--;
}

Torretta::~Torretta()
{
}