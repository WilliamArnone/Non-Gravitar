#include "TorrettaPro.h"



TorrettaPro::TorrettaPro()
{
}

TorrettaPro::TorrettaPro(float xu, float yu, float xl, float yl, float xr, float yr) :Torretta(xu, yu, xl, yl, xr, yr) {
	pro = true;
	TimeToShoot = 600;
}

void TorrettaPro::Update(float fElapsedTime, float Px, float Py) {
	angle = atan2f(Px - X, Y - Py);
	if (TimeToShoot <= 0)
		TimeToShoot = 600;
	else
		TimeToShoot--;
}


TorrettaPro::~TorrettaPro()
{
}
