#pragma once

#include <vector>
#include <ctime>

#include "objGame.hpp"
#include "Torretta.hpp"
#include "TorrettaPro.hpp"
#include "Carburante.hpp"
#include "CarburantePro.hpp"

class Area {
public:
	std::vector<objGame> Terreno; //Assieme di punti che compongono il terreno dell'area
	std::vector<Torretta> Torrette;
	std::vector<Carburante> Carburanti;

	objGame CreaPuntoTerreno(int ScreenWidthmin, int ScreenWidthmax, int ScreenHeight); //crea un punto appartenente al terreno dell'area 
	Area(int n, int ScreenWidth, int ScreenHeight, int LP); 
	float FindY(float xp); //funzione che restituisc l'altezza realtiva al punto x scelto di modo che venga posizionato esattamente sul terreno dell'area
	Torretta CreaTorretta(int ScreenWidth);
	Carburante CreaCarburanti(int ScreenWidth);
	void CreaTorrette(int ScreenWidth);
};