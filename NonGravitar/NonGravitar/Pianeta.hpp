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
	//Vector che contiene tutte le aree del pianeta, ogni pianeta ha un numero di aree dipendente la sua grandezza
	std::vector<Area> Aree;   

	//valore che ci permette di navigare tra le aree 
	int areaCorrente; 
	// colore del pianeta 
	short Colore; 


	Pianeta(int ScreenWidth, int ScreenHeight); 
	Pianeta();
	bool isEnded();
	~Pianeta();
};