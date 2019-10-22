#include "Area.h"

objGame Area::CreaPuntoTerreno(int ScreenWidthmin, int ScreenWidthmax, int ScreenHeight) {
	objGame punto;
	punto.X = 1 + ScreenWidthmin + rand() % (ScreenWidthmax - ScreenWidthmin);
	punto.Y = rand() % ScreenHeight / 4;
	punto.Y = ScreenHeight - punto.Y - 5;
	return punto;
}

Torretta Area::CreaTorretta(std::vector<objGame> Terreno, int ScreenWidth) {
	float x = (Terreno[0].X + 2) + rand() % (int)(ScreenWidth - Terreno[0].X - 4);
	if (rand() % 101 > 45)
		return Torretta(x, FindY(x) - ((FindY(x - 2) + FindY(x + 2)) / 32), x - 2, FindY(x - 2), x + 2, FindY(x + 2));
	else
		return TorrettaPro(x, FindY(x) - ((FindY(x - 2) + FindY(x + 2)) / 32), x - 2, FindY(x - 2), x + 2, FindY(x + 2));
}

Carburante Area::CreaCarburanti(std::vector<objGame> Terreno, int ScreenWidth) {
	float x = Terreno[0].X + rand() % (int)(ScreenWidth - Terreno[0].X);
	if (rand() % 101 < 35) {
		if (rand() % 101 > 70)
			return Carburante(x, FindY(x));
		else
			return CarburantePro(x, FindY(x));
	}
}

float Area::FindY(float xp) {
	for (int i = 0; i < Terreno.size() - 1; i++) { //vengono ciclati tutti i punti della'area per trovare in quale range � compreso il punto passato in ingresso
		if ((Terreno[i].X <= xp) && (xp < Terreno[i + 1].X)) {
			float y = ((xp - Terreno[i].X)*(Terreno[i + 1].Y - Terreno[i].Y) / (Terreno[i + 1].X - Terreno[i].X)) + Terreno[i].Y; //quando trovato il punto allora viene calcolata la y relativa usando la formula della retta passante per 2 punti e calcolando il punto sostituendo il valore alla x
			return y;
		}
	}
	return 10000; //valore arbitrariamente grande da restituire in caso non si trovi un range in cui � compreso il punto dato in ingresso 
}

Area::Area(int n, const int ScreenWidth, const int ScreenHeight, int LP) {
	objGame Inizio;
	Inizio.Y = LP; // il primo punto ha x uguale a 0 e y passata in ingresso (� la y dell'ultimo punto dell'area precedente) cos� da avere una continuit� nelle aree
	Inizio.X = 0;
	Terreno.push_back(Inizio);
	for (int i = 1; i < n - 2; i++) {
		Terreno.push_back(CreaPuntoTerreno(ScreenWidth* i / n, ScreenWidth* (i + 1) / n, ScreenHeight)); // per non avere tutti i punti ammassati assime ogni punto viene calcolato in una zona che varia in base al numero di punti dell'area
	}
	objGame fine = CreaPuntoTerreno(ScreenWidth* (n - 1) / n, ScreenWidth, ScreenHeight);
	fine.X = ScreenWidth; //l'ultimo punto ha solo la y random e la x corrisponde alla totalit� della schermata cos� da creare continuit� con le altre aree
	Terreno.push_back(fine);

	Torrette.push_back(CreaTorretta(Terreno, ScreenWidth));
	Carburanti.push_back(CreaCarburanti(Terreno, ScreenWidth));
}
