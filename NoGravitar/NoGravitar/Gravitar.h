#pragma once

#include "olcConsoleGameEngine.h"

class Gravitar : public olcConsoleGameEngine
{
public:
	Gravitar();
	~Gravitar();
protected:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override; 
};

