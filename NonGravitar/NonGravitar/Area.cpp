#include "Area.h"

objGame Area::CreaPuntoTerreno(int ScreenWidthmin, int ScreenWidthmax, int ScreenHeight) {
	objGame punto;
	punto.X = 1 + ScreenWidthmin + rand() % (ScreenWidthmax - ScreenWidthmin);
	punto.Y = rand() % ScreenHeight / 4;
	punto.Y = ScreenHeight - punto.Y;
	return punto;
}
Area::Area(int n, int ScreenWidth, int ScreenHeight) {
	Terreno.push_back(CreaPuntoTerreno(0, ScreenWidth/n, ScreenHeight));
	for (int i = 1; i < n-2; i++) {
		Terreno.push_back(CreaPuntoTerreno(ScreenWidth* i/n,ScreenWidth* (i+1)/n,ScreenHeight));
	}
	objGame fine;
	fine.X = ScreenWidth;
	fine.Y = ScreenHeight;
	Terreno.push_back(fine);
}
