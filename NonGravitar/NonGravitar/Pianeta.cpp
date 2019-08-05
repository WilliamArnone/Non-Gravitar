#include "Pianeta.h"



Pianeta::Pianeta()
{
}

Pianeta::Pianeta(int ScreenWidth, int ScreenHeight)
{
	const int nPoints = 10;
	for (int i = 0; i < nPoints; i++) {
		int min = ScreenWidth / nPoints * i;
		int max = ScreenWidth / nPoints * i+ ScreenWidth / nPoints;
		objGame t = objGame();
		Terreno.push_back(t);
	}
	size = 3 + rand() % 5;
	int posizione = ScreenWidth - 2 * size;
	x = size + rand() % posizione;
	if (x == (ScreenWidth / 2)) {
		x = x + 1;
	}
	posizione = ScreenHeight - 2 * size;
	y = size + rand() % posizione;
}

//float Pianeta::FIndY(float x1, float y1, float x2, float y2, float xp) {//fixare i punti critici, creano problemi i lati troppo ripidi dove le torrette (ad ora cerchi) vengono messe sotto terra e non ho sinceramente voglia di capire il perchè, gioco a perudo con tommy ora, 3 6 
//	return (((xp - x1)*(y2 - y1) / (x2 - x1)) + y1);
//}

objGame CreaPuntoTerreno(int ScreenWidthmin, int ScreenWidthmax, int ScreenHeight) {
	objGame Point = objGame();
	Point.angle = 0;
	Point.size = 1;
	Point.x = rand() % (ScreenWidthmax - ScreenWidthmin) + ScreenWidthmin;
	Point.y = ScreenHeight - rand() % ScreenHeight / 2;
	return Point;
}

Pianeta::~Pianeta()
{
}
