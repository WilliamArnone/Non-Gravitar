#pragma once

#include "objGame.hpp"
//Classe figlio di objgame, che identifica tutti i valori standard delle torrette
//Classe padre di CarburantePro
class Carburante : public objGame
{
public:
	float liter; //quantit� di carburante che restituisce alla navicella 
	bool pro; //controlla se � o meno pro

	Carburante(float x, float y); //inizializza il carburante 
	~Carburante();
};

