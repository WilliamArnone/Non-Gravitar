#include "Pianeta.hpp"


Pianeta::Pianeta() {}

Pianeta::Pianeta(const int ScreenWidth, const int ScreenHeight)
{
	//si setta l'area corrente, il colore (scelto a caso), la dimensione (scelto a caso) e  la posizione (scelto a caso)
	areaCorrente = 0;
	Colore = 6 + (rand() % 10);
	Size = 3 + rand() % 5;
	X = Size + rand() % (ScreenWidth - 2 * Size);
	Y = Size + rand() % (ScreenHeight - 2 * Size);
	int rnd = 5 + rand() % 15;
	//la prima area viene generata, fuori dal ciclo perchè così le successive possono essere calcolate sulla base delle sue impostazioni
	Area inizio = Area(rnd, ScreenWidth, ScreenHeight, ScreenHeight);
	Aree.push_back(inizio);
	//le aree sono il doppio della dimensione del pianeta
	for (int i = 1; i < Size * 2; i++) {
		//tutte le aree vengono generate con un numero di punti random
		rnd = 5 + rand() % 15;
		Area in = Area(rnd, ScreenWidth, ScreenHeight, Aree[i - 1].Terreno[Aree[i - 1].Terreno.size() - 1].Y);
		in.CreaOggetti(ScreenWidth);
		Aree.push_back(in);
	}
	//per l'ultima e la prima area viene cambiato il punto finale/ iniziale  per creare continuità
	Aree[0].Terreno[0].Y = Aree[2 * Size - 1].Terreno[Aree[2 * Size - 1].Terreno.size() - 1].Y;
	Aree[0].CreaOggetti(ScreenWidth);
}

bool Pianeta::isEnded() {
	// il pianeta è finito se tutte le torrette sono eliminate 
	for (auto &t : Aree)
	{
		if (t.Torrette.size() > 0)
			return false;
	}
	return true;
}

Pianeta::~Pianeta()
{
}
