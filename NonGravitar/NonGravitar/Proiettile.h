#pragma once

#include "objGame.h"

class Proiettile : public objGame
{
protected:
	float dx, dy;
public:
	//La variabile player identifica se il proiettile � stato sparato dal giocatore o no.
	bool player = false;

	Proiettile();
	Proiettile(bool p, float x, float y, float a);
	void Update(float fElapsedTime);
	~Proiettile();
};
