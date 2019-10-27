#pragma once
#include "Carburante.h"
//Classe figlio di Carburante, utlizzata per il secondo tipo di carburante
class CarburantePro : public Carburante
{
public:
	CarburantePro();
	CarburantePro(float x, float y);
	~CarburantePro();
};

