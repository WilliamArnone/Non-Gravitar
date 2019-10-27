#pragma once

#include <vector>
#include "objGame.hpp"
#include "Torretta.hpp"
#include "Carburante.hpp"
#include "Area.hpp"
#include <iostream>
#include <ctime>

class Pianeta : public objGame
{
public:
	std::vector<objGame> Terreno;
	std::vector<Torretta> Torrette;
	std::vector<Carburante> Carburanti;
	std::vector<Area> Aree; //Vector che contiene tutte le aree del pianeta, ogni pianeta ha un numero di aree dipendente la sua grandezza  

	int areaCorrente; //valore che ci permette di navigare tra le aree 
	short Colore; // colore del pianeta 


	Pianeta(int ScreenWidth, int ScreenHeight); //costruttore che inizializza il pianeta 
	Pianeta();
	bool isEnded();
	~Pianeta();
};