#pragma once

#include <vector>
#include <ctime>

#include "objGame.h"
#include "Torretta.h"
#include "Carburante.h"

class Area {
public:
	std::vector<objGame> Terreno;
	std::vector<Torretta> Torrette;
	std::vector<Carburante> Carburanti;

	objGame CreaPuntoTerreno(int ScreenWidthmin, int ScreenWidthmax, int ScreenHeight);
	Area(int n, int ScreenWidth, int ScreenHeight);
	float FindY(float xp);
	Torretta CreaTorretta(std::vector<objGame> Terreno, int ScreenWidth);
	Carburante CreaCarburanti(std::vector<objGame> Terreno, int ScreenWidth);
};