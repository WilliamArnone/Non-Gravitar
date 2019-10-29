#pragma once

#include "olcConsoleGameEngine.h"

#include <iostream>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <string>
#include <math.h>

#include "Pianeta.hpp"
#include "Proiettile.hpp"
#include "Navicella.hpp"
#include "Carburante.hpp"
#include "objGame.hpp"
#include "Torretta.hpp"

using namespace std;

class Gravitar : public olcConsoleGameEngine
{
public:
	Gravitar();
	~Gravitar();

protected:

	//variabile necessaria a far comparire e scomparire la scritta iniziale  
	float blink; 

	//variabili per la morte del giocatore, la fine del gioco e il raggio traente
	bool morto, gameover, rayOn; 
	//variabili per il punteggio e le vite del giocatore 
	int score, vite;

	//Pianeti della galassia
	std::vector<Pianeta> pianeti;

	//proiettili nel gioco
	std::vector<Proiettile> Proiettili;

	//puntatore al pianeta attivo
	Pianeta *pianetaAttivo;

	//personaggio giocatore 
	Navicella pg;

	void resetGame();
	void newUniverse();
	void reborn();
	void resetPG();
	void enterPlanet(Pianeta *newplanet);
	void exitPlanet();
	void EraseBullets(vector<Proiettile> &Proiettili);
	void resetTor();

	bool Collision(objGame obj1, objGame obj2);
	void WrapCoordinate();
	bool checkDistance(Pianeta p);
	Pianeta * PlanetLanding();
	void CheckCollisions();
	void changeArea();
	void carbnear();
	
	void updateTorr(float fElapsedTime);
	void updateBull(float fElapsedTime);
	void updateNav(float fElapsedTime);

	void DrawNav();
	void DrawPlanet(Pianeta planet);
	void DrawArea();
	void DrawTorr(Torretta torre);
	void DrawCarb(Carburante carb);
	void DrawBullet(Proiettile bullet);
	void DrawRay();
	void DrawTitle(float fElapsedTime);
	void DrawGameOver(float fElapsedTime);

	virtual bool OnUserCreate();
	virtual bool OnUserUpdate(float fElapsedTime);
};

