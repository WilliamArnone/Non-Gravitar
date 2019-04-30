#include <iostream>
#include "Game.h"

int main() {

	Game gravitar;
	gravitar.ConstructConsole(160, 100, 8, 8);
	gravitar.Start();

	return 0;
}