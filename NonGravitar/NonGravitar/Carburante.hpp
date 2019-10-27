#pragma once

#include "objGame.hpp"
//Classe figlio di objgame, che identifica tutti i valori standard delle torrette
//Classe padre di CarburantePro
class Carburante : public objGame
{
public:
	float liter;
	bool pro;

	Carburante();
	Carburante(float x, float y);
	~Carburante();
};

