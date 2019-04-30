#pragma once
#include "olcConsoleGameEngine.h"


class Game : public olcConsoleGameEngine
{
public:
	Game();
	~Game();
protected:
	bool OnUserCreate();
	bool OnUserUpdate(float fElapsedTime);
};

