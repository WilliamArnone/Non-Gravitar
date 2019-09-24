#include "Galassia.h"


Galassia::Galassia()
{
}

Galassia::Galassia(float screenwidth, float screenheight)
{
	
}

bool Galassia::checkDistance(Pianeta pianeti[], int i, int c) {
	for (int l = 0; l < i; l++) {
		if (abs(pianeti[c].xc - pianeti[l].xc) < (pianeti[c].r + pianeti[l].r + 1) || abs(pianeti[c].yc - pianeti[l].yc) < (pianeti[c].r + pianeti[l].r + 1)) {
			return  true;
		}
	}
	return false;
}
int Galassia::PlanetCollision() {
	for (int i = 0; i < 5; i++) {
		if (IsPointInsideCircle(pianeti[i].xc,pianeti[i].yc, pianeti[i].r, player.x1, player.y1)) {
			return i;
		}
	}
	return -1;
}
bool Galassia::IsPointInsideCircle(float cx, float cy, float radius, float x, float y) {
	return sqrt((x - cx)*(x - cx) + (y - cy)*(y - cy)) < radius;
}
Galassia::~Galassia()
{
}
