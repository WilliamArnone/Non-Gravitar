#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "olcConsoleGameEngine.h"
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
	
	bool morto,gameover;
	int score;
	
	std::vector<Pianeta> pianeti;

	std::vector<Proiettile> proiettili;

	Pianeta *pianetaAttivo;

	Navicella pg;

	void resetGame();
	void newUniverse();

	void enterPlanet(Pianeta *newplanet);
	void exitPlanet();

	bool carbnear();
	bool Collision(objGame obj1, objGame obj2);
	bool objCrashing();
	bool isLanding();
	bool isLeaving();
	Pianeta * checkPlanet();

	void updateTorr(float fElapsedTime);
	void updateBull(float fElapsedTime);
	void updateNav(float fElapsedTime);

	void clear();
	bool checkEnd();

	void reborn();

	void DrawNav();
	void DrawTorr(Torretta torre);
	void DrawCarb(Carburante carb);
	void DrawPlanet(Pianeta planet);
	void DrawBullet(Proiettile bullet);
	void DrawRay();
	void DrawGameOver();

	void ResetGame();

	virtual bool OnUserCreate();
	virtual bool OnUserUpdate(float fElapsedTime);
};

