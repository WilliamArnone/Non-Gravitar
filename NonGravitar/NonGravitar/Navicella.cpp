#include "Navicella.h"

Navicella::Navicella()
{
}

Navicella::~Navicella()
{
}

void Navicella::setShip(float width, float heigth) {
	x1 = width / 2.0f;
	y1 = heigth / 2.0f;
	x2 = 0;
	y2 = 0;
	angle = 0;
	life = 3;
	fuel = 10000;
}

void Navicella::ShipMove(float fElapsedTime, bool Up) {

	// Thrust? Apply ACCELERATION
	if (Up)
	{
		if (fuel >= 0) {
			fuel--;
			// ACCELERATION changes VELOCITY (with respect to time)
			if (x2 < 50 && y2 > -50) {
				x2 += sin(angle) * 15.0f * fElapsedTime;
				y2 += -cos(angle) * 15.0f * fElapsedTime;
			}
		}
	}
	else {
		x2 = 0;
		y2 = 0;
	}

	//Velocità finale
	x1 += x2 * fElapsedTime;
	y1 += y2 * fElapsedTime;
}

//Richiede sia il tempo che un valore per differenziare tra sinistra o destra
void Navicella::ShipRotate(float fElapsedTime, bool Left) {
	// Steer Ship
	if (Left)
		angle -= 5.0f * fElapsedTime;
	else
		angle += 5.0f * fElapsedTime;
}

/*void ChangeArea(){
	// Cambio zona
	if (x1 > ScreenWidth() &&) {
		vecBullets.clear();
		if (AreaCorrente < 9) {
			AreaCorrente++;
		}
		else {
			AreaCorrente = 0;
		}
	}
	if (x1 < 0 && position == 1) {
		vecBullets.clear();
		if (AreaCorrente > 0) {
			AreaCorrente--;
		}
		else {
			AreaCorrente = 9;
		}
	}
}*/


/*//Richiede la posizione della navicella
void Navicella::ShipShoot() {
	//Shooting Player's Bullet
	vecBullets.push_back({ 0, x1, y1 , 50.0f * sinf(angle), -50.0f * cosf(angle), 100.0f, true });
}*/