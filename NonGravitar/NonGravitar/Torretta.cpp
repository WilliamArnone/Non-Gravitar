#include "Torretta.h"

Torretta::Torretta()
{
}

Torretta::Torretta(float xu, float yu, float xl, float yl, float xr, float yr)
{
	TimeToShoot = 500;
	XUp = xu;
	YUp = yu;
	Xl = xl;
	Yl = yl;
	Xr = xr;
	Yr = yr;
	X = xu;
	Y = yu - 2;
}

void Torretta::Update(float fElapsedTime, float Px, float Py) {
	angle = atan2f(Px - X, Y - Py);
	TimeToShoot--;
}

Torretta::~Torretta()
{
}