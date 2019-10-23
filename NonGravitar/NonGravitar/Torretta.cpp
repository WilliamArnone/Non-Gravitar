#include "Torretta.h"

Torretta::Torretta()
{
}

Torretta::Torretta(float xu, float yu, float xl, float yl, float xr, float yr)
{
	//Baricentro Cerchio
	X = (XUp + Xl + Xr) / 3;
	Y = (YUp + Yl + Yr) / 3;

	XUp = xu;
	YUp = yu;
	Xl = xl;
	Yl = yl;
	Xr = xr;
	Yr = yr;

	list.clear();
	TimeToShoot = 500;
	pro = false;
}

void Torretta::Update(float fElapsedTime, float Px, float Py) {
	angle = atan2f(Px - XUp, YUp - Py);
	list.clear();
	if (TimeToShoot <= 0) {
		list.push_back({ false, XUp, YUp, angle - 0.08f });
		list.push_back({ false, XUp, YUp, angle + 0.08f });
		TimeToShoot = 500;
	}
	else
		TimeToShoot--;
}

Torretta::~Torretta()
{
}