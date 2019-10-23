#include "TorrettaPro.h"



TorrettaPro::TorrettaPro()
{
}

TorrettaPro::TorrettaPro(float x, float y, float Angle) : Torretta(x, y, Angle) {
	
	TimeToShoot = 200;
	pro = true;
}

void TorrettaPro::UpdatePro(float fElapsedTime, float Px, float Py) {
	angle = atan2f(Px - X, Y - Py);
	list.clear();
	if (TimeToShoot <= 0) {
		list.push_back({ false, X, Y, angle - 0.1f });
		list.push_back({ false, X, Y, angle });
		list.push_back({ false, X, Y, angle + 0.1f });
		TimeToShoot = 200;
	}
	else
		TimeToShoot=  TimeToShoot-1*fElapsedTime;
}



TorrettaPro::~TorrettaPro()
{
}
