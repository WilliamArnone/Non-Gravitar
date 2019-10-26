#include "TorrettaPro.h"

TorrettaPro::TorrettaPro() {}

TorrettaPro::~TorrettaPro() {}

TorrettaPro::TorrettaPro(float x, float y, float Angle) : Torretta(x, y, Angle) {

	TimeToShoot = 200;
	pro = true;
	Color = 4;
}

//L'updatePro di questa torretta è uguale all' update della torretta normale, se non fosse che questa sparà più proiettili
void TorrettaPro::UpdatePro(float fElapsedTime, float Px, float Py) {
	float anglep = atan2f(Px - X, Y - Py);
	TorreProiettili.clear();
	if (TimeToShoot <= 0) {
		TorreProiettili.push_back({ false, X + sinf(angle)*4.0f, Y - cosf(angle)*4.0f, anglep - 0.1f });
		TorreProiettili.push_back({ false, X + sinf(angle)*4.0f, Y - cosf(angle)*4.0f, anglep });
		TorreProiettili.push_back({ false, X + sinf(angle)*4.0f, Y - cosf(angle)*4.0f, anglep + 0.1f });
		TimeToShoot = 200;
	}
	else
		TimeToShoot = TimeToShoot - 1 * fElapsedTime;
}



