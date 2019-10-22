#pragma once

#include <vector>
#include <ctime>

#include "objGame.h"
#include "Torretta.h"
#include "Carburante.h"
#include "TorrettaPro.h"

class Area {
public:
	std::vector<objGame> Terreno;
	std::vector<Torretta> Torrette;
	std::vector<Carburante> Carburanti;

	objGame CreaPuntoTerreno(int n, const int ScreenWidth, const int ScreenHeight, int LP);
	Area(int n, int ScreenWidth, int ScreenHeight);
	float FindY(float xp);
	Torretta CreaTorretta(std::vector<objGame> Terreno, int ScreenWidth);
	Carburante CreaCarburanti(std::vector<objGame> Terreno, int ScreenWidth);
};