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

	float fuel, blink;

	bool morto, gameover, rayOn;
	int score, vite;

	std::vector<Pianeta> pianeti;

	std::vector<Proiettile> Proiettili;

	Pianeta *pianetaAttivo;

	Navicella pg;

	void resetGame();
	void newUniverse();
	bool checkDistance(vector<Pianeta> pianeti, Pianeta p);

	void enterPlanet(Pianeta *newplanet);
	void exitPlanet();

	void carbnear();
	bool Collision(objGame obj1, objGame obj2);
	Pianeta * PlanetLanding();
	void WrapCoordinate();
	void EraseBullets(vector<Proiettile> &Proiettili);

	void updateTorr(float fElapsedTime);
	void updateBull(float fElapsedTime);
	void updateNav(float fElapsedTime);

	void changeArea();
	
	void reborn();

	void DrawNav();
	void DrawTorr(Torretta torre);
	void DrawCarb(Carburante carb);
	void DrawPlanet(Pianeta planet);
	void DrawBullet(Proiettile bullet);
	void DrawRay();
	void DrawArea();
	void DrawTitle(float fElapsedTime);
	void DrawGameOver(float fElapsedTime);

	void CheckCollisions();

	virtual bool OnUserCreate();
	virtual bool OnUserUpdate(float fElapsedTime);
};

