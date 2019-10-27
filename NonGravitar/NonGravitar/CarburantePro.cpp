#include "CarburantePro.hpp"

CarburantePro::CarburantePro()
{
}

CarburantePro::CarburantePro(float x, float y) :Carburante(x, y)
{
	pro = true;
	liter = 500;
	Color = 1;
}

CarburantePro::~CarburantePro()
{
}
