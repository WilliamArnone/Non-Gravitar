#include "Navicella.h"

Navicella::Navicella()
{
}

Navicella::~Navicella()
{
}


void Navicella::ShipMove(float fElapsedTime, bool Up) {
	if (Up) {
		fuel--;
		dx += sin(angle) * 15.0f * fElapsedTime;
		dy += -cos(angle) * 15.0f * fElapsedTime;
	}
	else {
		fuel--;
		dx -= sin(angle) * 10.0f * fElapsedTime;
		dy -= -cos(angle) * 10.0f * fElapsedTime;
	}

}

//Richiede sia il tempo che un valore per differenziare tra sinistra o destra
void Navicella::ShipRotate(float fElapsedTime, bool Left) {
	// Steer Ship
	if (Left)
		angle -= 5.0f * fElapsedTime;
	else
		angle += 5.0f * fElapsedTime;
}
