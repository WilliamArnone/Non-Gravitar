#include "collision.h"



collision::collision()
{
}

bool collision::Collision(float x1, float y1, float x2, float y2, float xp, float yp,float ScreenHeight) {
	if (yp > ScreenHeight) {
		return true;
	}
	if (yp > (((xp - x1)*(y2 - y1) / (x2 - x1)) + y1)) {
		return true;
	}
	return false;
}
bool collision::Collision(float x1, float y1, float x2, float y2) {
	if (x1<x2 + 2 && x1>x2 - 2 && y1<y2 + 2 && y1>y2 - 2) {
		return true;
	}
	return false;
}
collision::~collision()
{
}
