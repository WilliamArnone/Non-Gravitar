#include "Area.h"

objGame Area::CreaPuntoTerreno(int ScreenWidthmin, int ScreenWidthmax, int ScreenHeight) {
	objGame punto;
	punto.X = 1 + ScreenWidthmin + rand() % (ScreenWidthmax - ScreenWidthmin);
	punto.Y = rand() % ScreenHeight / 4;
	punto.Y = ScreenHeight - punto.Y - 5;
	return punto;
}

Torretta Area::CreaTorretta(std::vector<objGame> Terreno, int ScreenWidth) {
	float x = 10 + rand() % (ScreenWidth - 20);
	if (rand() % 101 > 45)
		return Torretta(x, FindY(x) - ((FindY(x - 2) + FindY(x + 2)) / 32), x - 2, FindY(x - 2), x + 2, FindY(x + 2));
	else
		return TorrettaPro(x, FindY(x) - ((FindY(x - 2) + FindY(x + 2)) / 32), x - 2, FindY(x - 2), x + 2, FindY(x + 2));
}

Carburante Area::CreaCarburanti(std::vector<objGame> Terreno, int ScreenWidth) {
	if (rand() % 100 < 33) {
		float x = 10 + rand() % (ScreenWidth - 20);
		Carburante F = Carburante(x, FindY(x));
		return F;
	}
}

float Area::FindY(float xp) {
	for (int i = 0; i < Terreno.size() - 1; i++) {
		if ((Terreno[i].X <= xp) && (xp < Terreno[i + 1].X)) {
			float l = ((xp - Terreno[i].X)*(Terreno[i + 1].Y - Terreno[i].Y) / (Terreno[i + 1].X - Terreno[i].X)) + Terreno[i].Y;
			return l;
		}
	}
	return 0;
}

Area::Area(int n, const int ScreenWidth, const int ScreenHeight) {
	Terreno.push_back(CreaPuntoTerreno(0, ScreenWidth / n, ScreenHeight));
	for (int i = 1; i < n - 2; i++)
		Terreno.push_back(CreaPuntoTerreno(ScreenWidth* i / n, ScreenWidth* (i + 1) / n, ScreenHeight));

	objGame fine;
	fine.X = ScreenWidth;
	fine.Y = ScreenHeight;
	Terreno.push_back(fine);

	Torrette.push_back(CreaTorretta(Terreno, ScreenWidth));
	Carburanti.push_back(CreaCarburanti(Terreno, ScreenWidth));
}
