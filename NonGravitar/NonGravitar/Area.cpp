#include "Area.h"

objGame Area::CreaPuntoTerreno(int ScreenWidthmin, int ScreenWidthmax, int ScreenHeight) {
	objGame punto;
	punto.X = ScreenWidthmin + rand() % (ScreenWidthmax - ScreenWidthmin);
	punto.Y = rand() % ScreenHeight / (3/2);
	punto.Y = ScreenHeight - punto.Y;
	return punto;
}
void Area::CReaArea(int n, int ScreenWidth, int ScreenHeight) {
	Terreno.push_back(CreaPuntoTerreno(0, ScreenWidth / n, ScreenHeight));
	for (int i = 1; i < n-2; i++) {
		Terreno.push_back(CreaPuntoTerreno(Terreno[i-1].X,ScreenWidth/n,ScreenHeight));
	}
	objGame fine;
	fine.X = ScreenWidth;
	fine.Y = ScreenHeight;
	Terreno.push_back(fine);
}
