#pragma once

class objGame
{
public:
	objGame(float x, float y, float size);

	objGame();
	~objGame();
	//identificatori del punto
	float X, Y;
	//raggio del cerchio
	int Size;
	//colore del cerchiio
	short Color;
	//angolo
	float angle;
};