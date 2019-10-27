#include "TorrettaPro.hpp"



TorrettaPro::TorrettaPro()
{
}

TorrettaPro::TorrettaPro(float x, float y, float Angle) : Torretta(x, y, Angle) {
	
	TimeToShoot = 300;
	pro = true;
	Color = 4;
}

void TorrettaPro::UpdatePro(float fElapsedTime, float Px, float Py) {
	float anglep = atan2f(Px - X, Y - Py);
	list.clear();
	if (TimeToShoot <= 0) {
		list.push_back({ false, X+sinf(angle)*4.0f, Y-cosf(angle)*4.0f, anglep - 0.1f });
		list.push_back({ false, X+sinf(angle)*4.0f, Y-cosf(angle)*4.0f, anglep });
		list.push_back({ false, X+sinf(angle)*4.0f, Y-cosf(angle)*4.0f, anglep + 0.1f });
		TimeToShoot = 200;
	}
	else
		TimeToShoot=  TimeToShoot-1*fElapsedTime;
}



TorrettaPro::~TorrettaPro()
{
}
