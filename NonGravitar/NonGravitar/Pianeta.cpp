#include "Pianeta.h"



Pianeta::Pianeta(int ScreenWidth, int ScreenHeight, int numeroAree)
{
	areaCorrente = 0;
	Colore = rand() % 15;
	const int nPoints = 10;
	for (int i = 0; i < nPoints; i++) {
		int min = ScreenWidth / nPoints * i;
		int max = ScreenWidth / nPoints * i+ ScreenWidth / nPoints;
		objGame t = objGame();
		Terreno.push_back(t);
	}
	Size = 3 + rand() % 5;
	int posizione = ScreenWidth - 2 * Size;
	X = Size + rand() % posizione;
	if (X == (ScreenWidth / 2)) {
		X = X + 1;
	}
	posizione = ScreenHeight - 2 * Size;
	Y = Size + rand() % posizione;
	for (int i = 0; i < numeroAree; i++) {
		Area in = Area(10,ScreenWidth,ScreenHeight);
		Aree.push_back(in);
	}
}

float Pianeta::FIndY(float x1, float y1, float x2, float y2, float xp) {//fixare i punti critici, creano problemi i lati troppo ripidi dove le torrette (ad ora cerchi) vengono messe sotto terra e non ho sinceramente voglia di capire il perchè, gioco a perudo con tommy ora, 3 6 
	return (((xp - x1)*(y2 - y1) / (x2 - x1)) + y1);
}

objGame CreaPuntoTerreno(int ScreenWidthmin, int ScreenWidthmax, int ScreenHeight) {
	objGame Point = objGame();
	Point.angle = 0;
	Point.Size = 1;
	Point.Color = rand() % 255;
	Point.X = rand() % (ScreenWidthmax - ScreenWidthmin) + ScreenWidthmin;
	Point.Y = ScreenHeight - rand() % ScreenHeight / 2;
	return Point;
}
Torretta CreaTorretta(int ScreenWidthmin, int ScreenWidthmax, int ScreenHeight) {

	//Scrivete

	return Torretta();
}
Carburante CreaCarburante(int ScreenWidthmin, int ScreenWidthmax, int ScreenHeight) {

	//Scrivete

	return Carburante();
}

Pianeta::~Pianeta()
{
}
