#pragma once
#include "objGame.h"
#include <iostream>
#include <ctime>
class Area
{
public:
	float x[5];
	float y[5];
	Area();
	Area(float ScreenWidth, float ScreenHeight);
	~Area();
};