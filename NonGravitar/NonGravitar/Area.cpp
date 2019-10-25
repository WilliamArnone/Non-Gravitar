#include "Area.h"

objGame Area::CreaPuntoTerreno(int ScreenWidthmin, int ScreenWidthmax, int ScreenHeight) {
	objGame punto;
	punto.X = 1 + ScreenWidthmin + rand() % (ScreenWidthmax - ScreenWidthmin);
	punto.Y = rand() % ScreenHeight / 4;
	punto.Y = ScreenHeight - punto.Y - 5;
	return punto;
}

//Viene creata una torretta in un punto casuale della mappa
Torretta Area::CreaTorretta(int ScreenWidth) {
	float x1, x2, y1, y2, angle;
	float x = 10 + rand() % (int)(ScreenWidth-20);
	float y = FindY(x);

	for (auto &p : Terreno) {
		if (p.X < x) {
			x1 = p.X;
			y1 = p.Y;
		}
		if (p.X > x) {
			x2 = p.X;
			y2 = p.Y;
			break;
		}
	}

	angle = atan((y2 - y1) / (x2 - x1)) + 3.14;

	if (rand() % 101 < 71)
		return Torretta(x,FindY(x), angle);
	else
		return TorrettaPro(x, FindY(x), angle);
}

Carburante Area::CreaCarburanti(int ScreenWidth) {
	float x = 10 + rand() % (int)(ScreenWidth - 10);
	if ((rand() % 101) > 70)
		return Carburante(x, FindY(x));
	else
		return CarburantePro(x, FindY(x));
	
}

float Area::FindY(float xp) {
	//vengono ciclati tutti i punti della'area per trovare in quale range è compreso il punto passato in ingresso
	for (int i = 0; i < Terreno.size() - 1; i++) { 
		if ((Terreno[i].X <= xp) && (xp < Terreno[i + 1].X)) {
			//quando trovato il punto allora viene calcolata la y relativa usando la formula della retta passante per 2 punti e calcolando il punto sostituendo il valore alla x
			float y = ((xp - Terreno[i].X)*(Terreno[i + 1].Y - Terreno[i].Y) / (Terreno[i + 1].X - Terreno[i].X)) + Terreno[i].Y; 
			return y;
		}
	}
	//valore arbitrariamente grande da restituire in caso non si trovi un range in cui è compreso il punto dato in ingresso 
	return 10000; 
}

Area::Area(int n, const int ScreenWidth, const int ScreenHeight, int LP) {

	// il primo punto ha x uguale a 0 e y passata in ingresso (è la y dell'ultimo punto dell'area precedente) così da avere una continuità nelle aree
	objGame Inizio;
	Inizio.Y = LP; 
	Inizio.X = 0;
	Terreno.push_back(Inizio);

	// per non avere tutti i punti ammassati assieme ogni punto viene calcolato in una zona che varia in base al numero di punti dell'area
	for (int i = 1; i < n - 2; i++) {
		Terreno.push_back(CreaPuntoTerreno(ScreenWidth* i / n, ScreenWidth* (i + 1) / n, ScreenHeight)); 
	}

	//l'ultimo punto ha solo la y random e la x corrisponde alla totalità della schermata così da creare continuità con le altre aree
	objGame fine = CreaPuntoTerreno(ScreenWidth* (n - 1) / n, ScreenWidth, ScreenHeight);
	fine.X = ScreenWidth; 
	Terreno.push_back(fine);

	//Viene creata una torretta in maniera casuale
	while ((rand() % 101) <= 51) {
		Torrette.push_back(CreaTorretta(ScreenWidth));
	}

	while ((rand() % 101) < 31) {
		Carburanti.push_back(CreaCarburanti(ScreenWidth));
	}
}
