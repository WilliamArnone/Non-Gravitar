#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
using namespace std;

#include "Gravitar.h"

int main() {

	
	Gravitar game;
	game.ConstructConsole(160, 100, 10, 10);
	game.Start();
	return 0;
}