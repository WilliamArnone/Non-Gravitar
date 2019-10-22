#include "TorrettaPro.h"



TorrettaPro::TorrettaPro()
{
}

TorrettaPro::TorrettaPro(float xu, float yu, float xl, float yl, float xr, float yr) :Torretta(xu, yu, xl, yl, xr, yr) {
	X = (XUp + Xl + Xr) / 3;
	Y = (YUp + Yl + Yr) / 3;
	TimeToShoot = 600;
	pro = true;
}

void TorrettaPro::UpdatePro(float fElapsedTime, float Px, float Py) {
	angle = atan2f(Px - X, Y - Py);
	list.clear();
	if (TimeToShoot <= 0) {
		list.push_back({ false, XUp, YUp, angle - 0.1f });
		list.push_back({ false, XUp, YUp, angle });
		list.push_back({ false, XUp, YUp, angle + 0.1f });
		TimeToShoot = 600;
	}
	else
		TimeToShoot--;
}



TorrettaPro::~TorrettaPro()
{
}
