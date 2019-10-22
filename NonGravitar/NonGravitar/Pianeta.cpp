#include "Pianeta.h"


Pianeta::Pianeta(){}
Pianeta::Pianeta(const int ScreenWidth, const int ScreenHeight)
{
	areaCorrente = 0; 
	Colore = (rand() % 14)+1; //si sceglie un colore random tra quelli disponibili nella console windows 
	Size = 3 + rand() % 5;     
	X = Size + rand() % (ScreenWidth - 2 * Size); // viene scelto casualmente un punto in cui inserire il pianeta all'interno della galassia (senza sforare i limiti della schermata )
	Y = Size + rand() % (ScreenHeight - 2 * Size);
	int rnd = 5 + rand() % 15;
	Area inizio = Area(rnd, ScreenWidth, ScreenHeight,ScreenHeight); //la prima area viene generata, fuori dal ciclo perchè così le successive possono essere calcolate sulla base delle sue impostazioni
	Aree.push_back(inizio);
	for (int i = 1; i < Size*2; i++) {
		rnd = 5 + rand() % 15;
		Area in = Area(rnd,ScreenWidth,ScreenHeight,Aree[i-1].Terreno[Aree[i-1].Terreno.size()-1].Y); 
		Aree.push_back(in);
	}
	Aree[Size*2 - 1].Terreno[Aree[Size*2 - 1].Terreno.size() - 1].Y = ScreenHeight;
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
