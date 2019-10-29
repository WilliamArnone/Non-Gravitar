#include "TorrettaPro.hpp"



TorrettaPro::TorrettaPro()
{
}

TorrettaPro::TorrettaPro(float x, float y, float Angle) : Torretta(x, y, Angle) {
	
	TimeToShoot = 400;
	pro = true;
	Color = 4;
}

void TorrettaPro::UpdatePro(float fElapsedTime, float Px, float Py) {
	float anglep = atan2f(Px - X, Y - Py);
	TorreProiettili.clear();
	if (TimeToShoot <= 0) {
		TorreProiettili.push_back({ false, X+sinf(angle)*4.0f, Y-cosf(angle)*4.0f, anglep - 0.1f });
		TorreProiettili.push_back({ false, X+sinf(angle)*4.0f, Y-cosf(angle)*4.0f, anglep });
		TorreProiettili.push_back({ false, X+sinf(angle)*4.0f, Y-cosf(angle)*4.0f, anglep + 0.1f });
		TimeToShoot = 400;
	}
	else
		TimeToShoot=  TimeToShoot-1*fElapsedTime;
}



TorrettaPro::~TorrettaPro()
{
}
