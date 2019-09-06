#pragma once

#include "objGame.h"

class Proiettile : public objGame
{
protected:
	int nSize;
	float x;
	float y;
	float dx;
	float dy;
	float angle;
	bool player = false;
	vector<Proiettile> vecBullets;
public:
	Proiettile();
	void BulletUpdate(float fElapsedTime);
	~Proiettile();
};

