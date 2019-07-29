#pragma once

#include "objGame.h"

class Pianeta : objGame
{
public:
	Pianeta();

	vector<objGame> Terreno;
	vector<Torretta> Torrette;
	vector<Carburante> Carburanti;
	bool isEnded();
	int Colore;

	~Pianeta();
};

