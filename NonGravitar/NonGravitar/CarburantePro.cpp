#include "CarburantePro.h"

CarburantePro::CarburantePro(){}

CarburantePro::~CarburantePro(){}

//A differenza di Carburante, di cui CarburantePro è il figlio i valori per il colore e i litri cambiano
CarburantePro::CarburantePro(float x, float y) :Carburante(x, y)
{
	pro = true;
	liter = 500;
	Color = 1;
}

