#pragma once

#include <vector>
#include "objGame.h"
#include "Torretta.h"
#include "Carburante.h"
#include <ctime>

class Area {
public:
	std::vector<objGame> Terreno;
	std::vector<Torretta> Torrette;
	std::vector<Carburante> Carburanti;

	objGame CreaPuntoTerreno(int ScreenWidthmin, int ScreenWidthmax, int ScreenHeight);
	Area(int n, int ScreenWidth, int ScreenHeight, int LP);
	float FindY(float xp);
	Torretta CreaTorretta(int ScreenWidthmin, int ScreenWidthmax, int ScreenHeight);
	Torretta CreaCarburanti(int ScreenWidthmin, int ScreenWidthmax, int ScreenHeight);
};