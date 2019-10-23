#pragma once

#include "objGame.h"

class Proiettile : public objGame
{
protected:
	float dx, dy;
public:
	bool player = false;
	Proiettile();
	Proiettile(bool p, float x, float y, float a);
	void Update(float fElapsedTime);
	~Proiettile();
};
