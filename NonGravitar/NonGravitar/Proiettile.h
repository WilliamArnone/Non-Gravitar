#pragma once

#include "objGame.h"

class Proiettile : public objGame
{
protected:
	bool player = false;
	float dx, dy;
public:
	Proiettile();
	Proiettile(bool p, float x, float y, float a);
	void Update(float fElapsedTime);
	~Proiettile();
};
