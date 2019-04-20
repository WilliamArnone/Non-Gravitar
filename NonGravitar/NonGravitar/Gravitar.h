#pragma once

#include "olcConsoleGameEngine.h"

class Gravitar : public olcConsoleGameEngine
{
public:
	Gravitar();
	~Gravitar();

protected:
	virtual bool OnUserCreate();
	void ResetGame();
	virtual bool OnUserUpdate(float fElapsedTime);
};

