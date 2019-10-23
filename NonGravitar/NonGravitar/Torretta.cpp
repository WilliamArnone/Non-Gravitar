#include "Torretta.h"

Torretta::Torretta()
{
}

Torretta::Torretta(float xu, float yu, float xl, float yl, float xr, float yr)
{
	//Baricentro Cerchio

	XUp = xu;
	YUp = yu;
	Xl = xl;
	Yl = yl;
	Xr = xr;
	Yr = yr;

	X = (XUp + Xl + Xr) / 3;
	Y = (YUp + Yl + Yr) / 3;

	list.clear();
	TimeToShoot = 200;
	pro = false;
	Size = 2;
}

void Torretta::Update(float fElapsedTime, float Px, float Py) {
	angle = atan2f(Px - XUp, YUp - Py);
	list.clear();
	if (TimeToShoot <= 0) {
		list.push_back({ false, XUp, YUp, angle - 0.08f });
		list.push_back({ false, XUp, YUp, angle + 0.08f });
		TimeToShoot = 200;
	}
	else
		TimeToShoot= TimeToShoot-1*fElapsedTime;
}

Torretta::~Torretta()
{
}