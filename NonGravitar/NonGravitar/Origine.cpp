#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
using namespace std;

#include "Gravitar.hpp"

int main() {
	Gravitar game;
	int pixel = 10;
	while (game.ConstructConsole(160,100,pixel,pixel)!=1)
	{
		pixel= pixel - 1;
	}
	game.Start();
	return 0;
}