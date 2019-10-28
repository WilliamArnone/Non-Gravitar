#pragma once

#include "objGame.hpp"

class Proiettile : public objGame
{
public:
	//La variabile player identifica se il proiettile è stato sparato dal giocatore o no.
	bool player = false;

	Proiettile();
	Proiettile(bool p, float x, float y, float a);
	void Update(float fElapsedTime);
	~Proiettile();
};
