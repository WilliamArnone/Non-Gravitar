#pragma once

#include <vector>
#include "objGame.h"
#include "Torretta.h"
#include "Carburante.h"

class Pianeta : objGame
{
public:
	Pianeta();

	std::vector<objGame> Terreno;
	std::vector<Torretta> Torrette;
	std::vector<Carburante> Carburanti;

	int Colore;
	bool isEnded();

	~Pianeta();
};

