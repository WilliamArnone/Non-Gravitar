#pragma once

#include "objGame.h"

class Proiettile : public objGame
{
public:
	bool player = false;
	Proiettile();
	Proiettile(bool p, float x, float y, float a);
	void Update(float fElapsedTime);
	~Proiettile();
};
