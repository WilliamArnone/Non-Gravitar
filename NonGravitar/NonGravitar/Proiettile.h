#pragma once

#include "objGame.h"

class Proiettile : public objGame
{
public:
	Proiettile();
	void Update(float fElapsedTime);
	~Proiettile();
};

