#pragma once

#include <vector>
#include "objGame.h"
#include "Torretta.h"
#include "Carburante.h"
#include "Area.h"
#include <iostream>
#include <ctime>

class Pianeta : public objGame
{
public:
	Pianeta();
	Pianeta(int ScreenWidth, int ScreenHeight);
  	std::vector<objGame> Terreno;
	std::vector<Torretta> Torrette;
	std::vector<Carburante> Carburanti;
	std::vector<Area> Aree;

	int areaCorrente;
	short Colore;
	bool isEnded();
	objGame CreaPuntoTerreno(int ScreenWidthmin, int ScreenWidthmax, int ScreenHeight);
	Torretta CreaTorretta(int ScreenWidthmin, int ScreenWidthmax, int ScreenHeight);
	Torretta CreaCarburanti(int ScreenWidthmin, int ScreenWidthmax, int ScreenHeight);
	~Pianeta();
};