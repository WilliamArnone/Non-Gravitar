#include "Area.h"

objGame Area::CreaPuntoTerreno(int ScreenWidthmin, int ScreenWidthmax, int ScreenHeight) {
	objGame punto;
	punto.X = 1 + ScreenWidthmin + rand() % (ScreenWidthmax - ScreenWidthmin);
	punto.Y = rand() % ScreenHeight / 4;
	punto.Y = ScreenHeight - punto.Y - 5;
	return punto;
}
float Area::FindY(float xp) {
	for (int i = 0; i < Terreno.size()-1; i++) {
		if ((Terreno[i].X <= xp) && (xp < Terreno[i + 1].X)) {
			float y= ((xp - Terreno[i].X)*(Terreno[i + 1].Y- Terreno[i].Y) / (Terreno[i + 1].X - Terreno[i].X)) + Terreno[i].Y;
			return y;
		}
	}
	return 10000;
}

Area::Area(int n, const int ScreenWidth, const int ScreenHeight, int LP = 0) {
	objGame Inizio;
	Inizio.Y = LP;
	Inizio.X = 0;
	Terreno.push_back(Inizio);
	for (int i = 1; i < n-2; i++) {
		Terreno.push_back(CreaPuntoTerreno(ScreenWidth* i/n,ScreenWidth* (i+1)/n,ScreenHeight));
	}
	objGame fine = CreaPuntoTerreno(ScreenWidth* (n - 1) / n, ScreenWidth, ScreenHeight);
	fine.X = ScreenWidth;
	Terreno.push_back(fine);
}
