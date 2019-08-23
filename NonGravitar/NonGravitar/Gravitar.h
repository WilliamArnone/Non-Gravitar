#pragma once

#include "olcConsoleGameEngine.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>
#include <math>

#include "Pianeta.h"
#include "Proiettile.h"
#include "Navicella.h"
#include "Carburante.h"
#include "objGame.h"
#include "Torretta.h"

using namespace std;


class Gravitar : public olcConsoleGameEngine
{
public:
	Gravitar();
	~Gravitar();

protected:
	bool morto;
	int score;
	
	vector<Pianeta> pianeti;

	vector<Proiettile> proiettili;

	Pianeta *pianetaAttivo;

	Navicella pg;

	void resetGame();
	void newUniverse();

	void enterPlanet(Pianeta *newplanet);
	void exitPlanet();

	bool carbnear();
	bool bulletcollision(objGame oggetto, Proiettile bullet);
	bool objCrashing();
	bool isLanding();
	bool isLeaving();

	void updateTorr();
	void updateBull();
	void updateNav();

	void clear();
	bool checkEnd();

	void gameover();
	void reborn();

	void DrawNav();
	void DrawTorr(Torretta torre);
	void DrawCarb(Carburante carb);
	void DrawPlanet(Pianeta planet);
	void DrawBullet(Proiettile bullet);
	void DrawRay();

	void ResetGame();

	virtual bool OnUserCreate();
	virtual bool OnUserUpdate(float fElapsedTime);
};

