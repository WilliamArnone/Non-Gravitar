#pragma once

#include <vector>
#include "objGame.h"
#include "Torretta.h"
#include "Carburante.h"
#include <iostream>
#include <ctime>

class Pianeta : public objGame
{
public:
	Pianeta(int ScreenWidth, int ScreenHeight);
  	std::vector<objGame> Terreno;
	std::vector<Torretta> Torrette;
	std::vector<Carburante> Carburanti;

	int Colore;
	bool isEnded();
	objGame CreaPuntoTerreno(int ScreenWidthmin, int ScreenWidthmax, int ScreenHeight);
	Torretta CreaTorretta(int ScreenWidthmin, int ScreenWidthmax, int ScreenHeight);
	Torretta CreaCarburanti(int ScreenWidthmin, int ScreenWidthmax, int ScreenHeight);
	float FIndY(float x1, float y1, float x2, float y2, float xp); //restituisce la y corrispondenta 
	~Pianeta();
};

