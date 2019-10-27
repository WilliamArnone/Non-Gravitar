#include "Pianeta.hpp"


Pianeta::Pianeta(){}

Pianeta::Pianeta(const int ScreenWidth, const int ScreenHeight)
{
	areaCorrente = 0; 
	Colore = 6 + (rand() % 10); //si sceglie un colore random tra quelli disponibili nella console windows 
	Size = 3 + rand() % 5;     
	X = Size + rand() % (ScreenWidth - 2 * Size); // viene scelto casualmente un punto in cui inserire il pianeta all'interno della galassia (senza sforare i limiti della schermata )
	Y = Size + rand() % (ScreenHeight - 2 * Size);
	int rnd = 5 + rand() % 15;
	Area inizio = Area(rnd, ScreenWidth, ScreenHeight,ScreenHeight); //la prima area viene generata, fuori dal ciclo perchè così le successive possono essere calcolate sulla base delle sue impostazioni
	Aree.push_back(inizio);
	for (int i = 1; i < Size*2; i++) {
		rnd = 5 + rand() % 15;
		Area in = Area(rnd,ScreenWidth,ScreenHeight,Aree[i-1].Terreno[Aree[i-1].Terreno.size()-1].Y); 
		in.CreaTorrette(ScreenWidth);
		Aree.push_back(in);
	}
	int Y = rand() % ScreenHeight / 4;
	Y = ScreenHeight - Y - 5;
	Aree[0].Terreno[0].Y = Y;
	Aree[0].CreaTorrette(ScreenWidth);
	Aree[Size * 2 - 1].Terreno[Aree[Size * 2 - 1].Terreno.size() - 1].Y = Y;
	Aree[Size * 2 - 1].CreaTorrette(ScreenWidth);
}

bool Pianeta::isEnded() {
	bool dead = true;
	for (auto &t : Aree)
	{
		if (t.Torrette.size() > 0)
			dead = false;
	}
	return dead;
}

Pianeta::~Pianeta()
{
}
