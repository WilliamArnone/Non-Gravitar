#include "Pianeta.h"



Pianeta::Pianeta()
{
}

Pianeta::Pianeta(float ScreenWidth, float ScreenHeight)
{
	for (int i = 0; i < 10; i++) {
		Aree[i] = Area(ScreenWidth,ScreenHeight);
	}
	r = 3 + rand() % 5;
	int posizione = ScreenWidth - 2 * r;
	xc = r + rand() % posizione;
	if (xc == (ScreenWidth / 2)) {
		xc = xc + 1;
	}
	posizione = ScreenHeight - 2 * r;
	yc = r + rand() % posizione;
}
float Pianeta::FIndY(float x1, float y1, float x2, float y2, float xp) {//fixare i punti critici, creano problemi i lati troppo ripidi dove le torrette (ad ora cerchi) vengono messe sotto terra e non ho sinceramente voglia di capire il perchè, gioco a perudo con tommy ora, 3 6 
	return (((xp - x1)*(y2 - y1) / (x2 - x1)) + y1);
}

Pianeta::~Pianeta()
{
}
