#include "Torretta.h"

Torretta::Torretta()
{
}

Torretta::Torretta(float x, float y, float Angle):objGame(x, y, 2)
{
	angle = Angle;

	list.clear();
	TimeToShoot = 200;
	pro = false;
}

void Torretta::Update(float fElapsedTime, float Px, float Py) {
	angle = atan2f(Px - X, Y - Py);
	list.clear();
	if (TimeToShoot <= 0) {
		list.push_back({ false, X, Y, angle - 0.08f });
		list.push_back({ false, X, Y, angle + 0.08f });
		TimeToShoot = 200;
	}
	else
		TimeToShoot= TimeToShoot-1*fElapsedTime;
}

Torretta::~Torretta()
{
}