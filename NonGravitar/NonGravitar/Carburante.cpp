#include "Carburante.h"



Carburante::Carburante()
{
}


Carburante::~Carburante()
{
}

bool Carburante::CarbNear(Carburante F) {
	if (IsPointInsideCircle(F.c.xc, F.c.yc, F.c.r + 5, player.x1, player.y1) == true)
		return true;
}
