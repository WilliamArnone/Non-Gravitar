#pragma once

#include <vector>
#include "objGame.h"
#include "Torretta.h"
#include "Carburante.h"
#include <iostream>
#include <ctime>
#include "Area.h"

class Pianeta : objGame
{
public:
	float xc; //coordinate x,y e raggio del cerchio rappresentante il pianeta 
	float yc;
	float r;
	Area Aree[10]; //aree interne al pianeta
	Pianeta();
  	std::vector<objGame> Terreno;
	std::vector<Torretta> Torrette;
	std::vector<Carburante> Carburanti;

	int Colore;
	bool isEnded();

	Pianeta(float ScreenWidth, float ScreenHeight); //setta il pianeta
	float FIndY(float x1, float y1, float x2, float y2, float xp); //restituisce la y corrispondenta 
	~Pianeta();
};

