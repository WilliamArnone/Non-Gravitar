#include "Pianeta.h"



Pianeta::Pianeta(const int ScreenWidth, const int ScreenHeight, int numeroAree)
{
	areaCorrente = 0;
	Colore = (rand() % 14)+1;
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
	Area inizio = Area(10, ScreenWidth, ScreenHeight,ScreenHeight);
	Aree.push_back(inizio);
	for (int i = 1; i < numeroAree; i++) {
		Area in = Area(10,ScreenWidth,ScreenHeight,Aree[i-1].Terreno[Aree[i-1].Terreno.size()-1].Y);
		Aree.push_back(in);
	}
	Aree[numeroAree - 1].Terreno[Aree[numeroAree - 1].Terreno.size() - 1].Y = ScreenHeight;
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
