#include "Proiettile.h"
#include <math.h>

Proiettile::Proiettile() {}

Proiettile::~Proiettile() {}

//Viene inzializzato il proiettile, dinstinguendolo tra giocatore e torretta applicandogli i rispettivi colori e inserendogli l'angolo iniziale
Proiettile::Proiettile(bool p, float x, float y, float a) : objGame(x, y, 1) {
	player = p;
	angle = a;
	Color = p ? 15 : 4;
}

//Il proiettile modifica la sua X ed Y nel tempo seguendo l'angolo inziale prefissato
void Proiettile::Update(float fElapsedTime) {
	X += 75.0f * sinf(angle) * fElapsedTime;
	Y += -75.0f * cosf(angle) * fElapsedTime;
}