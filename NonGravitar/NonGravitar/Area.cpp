#include "Area.h"
Area::Area()
{
}
Area::Area(float ScreenWidth, float ScreenHeight) {
	for (int i = 0; i < 4; i++) {
		x[i] = rand() % ScreenWidth / 5;
		x[i] = x[i] + ScreenWidth*i / 5 + 6;
		y[i] = rand() % ScreenHeight / 2;
		y[i] = ScreenHeight - y[i];
	}
	x[4] = ScreenWidth;
	y[4] = ScreenHeight;
}
