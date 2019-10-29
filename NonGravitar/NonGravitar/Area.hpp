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
	std::vector<objGame> Terreno; //Vector di punti che compongono il terreno dell'area
	std::vector<Torretta> Torrette; //Vector di torrette presenti nell'area (normali e pro)
	std::vector<Carburante> Carburanti; //Vector di carburanti presenti nell'area (normali e pro)

	objGame CreaPuntoTerreno(int ScreenWidthmin, int ScreenWidthmax, int ScreenHeight); //crea un punto appartenente al terreno dell'area 
	Area(int n, int ScreenWidth, int ScreenHeight, int LP);  //Costruttore per l'inizializzazione e creazione dell'area
	float FindY(float xp); //funzione che restituisc l'altezza realtiva al punto x scelto di modo che venga posizionato esattamente sul terreno dell'area
	Torretta CreaTorretta(int ScreenWidth); //Crea la singola torretta
	Carburante CreaCarburante(int ScreenWidth); //Crea il singolo carburante 
	void CreaOggetti(int ScreenWidth); //Crea tutti gli oggetti presenti nell'area
};