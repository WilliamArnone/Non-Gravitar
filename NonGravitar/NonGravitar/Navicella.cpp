#include "Navicella.hpp"

Navicella::Navicella()
{
}

Navicella::~Navicella()
{
}


void Navicella::ShipMove(float fElapsedTime, bool Up) { 
	//aggiorna il carburante del giocatore 
	fuel -= 4 * fElapsedTime;
	//se il personaggio in avantiva più velocemente che all'indietro
	if (Up) {
		dx += sin(angle) * 20.0f * fElapsedTime;
		dy += -cos(angle) * 20.0f * fElapsedTime;
	}
	else {
		dx -= sin(angle) * 15.0f * fElapsedTime;
		dy -= -cos(angle) * 15.0f * fElapsedTime;
	}

}

void Navicella::ShipRotate(float fElapsedTime, bool Left) {
	//Richiede sia il tempo che un valore per differenziare tra sinistra o destra e ruota di conseguenza la navicella
	if (Left)
		angle -= 5.0f * fElapsedTime;
	else
		angle += 5.0f * fElapsedTime;
}
