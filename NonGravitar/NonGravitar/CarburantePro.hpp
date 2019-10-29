#pragma once
#include "Carburante.hpp"
//Classe figlio di Carburante, utlizzata per il secondo tipo di carburante
class CarburantePro : public Carburante
{
public:
	CarburantePro(float x, float y); //inizializza il CarburantePro
	~CarburantePro();
};

