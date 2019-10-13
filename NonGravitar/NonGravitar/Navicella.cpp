#include "Navicella.h"

Navicella::Navicella()
{
}

Navicella::~Navicella()
{
}

void Navicella::setShip(float width, float heigth) {

}

void Navicella::ShipMove(float fElapsedTime, bool Up) {

}

//Richiede sia il tempo che un valore per differenziare tra sinistra o destra
void Navicella::ShipRotate(float fElapsedTime, bool Left) {
	// Steer Ship
	if (Left)
		angle -= 5.0f * fElapsedTime;
	else
		angle += 5.0f * fElapsedTime;
}


/*//Richiede la posizione della navicella
void Navicella::ShipShoot() {
	//Shooting Player's Bullet
	vecBullets.push_back({ 0, x1, y1 , 50.0f * sinf(angle), -50.0f * cosf(angle), 100.0f, true });
}*/