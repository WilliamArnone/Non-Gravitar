#include "Carburante.h"

Carburante::Carburante(){}

Carburante::~Carburante(){}

//Viene inizializzato il carburante, dandogli la sua posizione, la dimensione di ObjGame e il valore di colore e di litri scelto per Carburante
Carburante::Carburante(float x, float y) {
	X = x;
	Y = y;
	Size = 1;
	liter = 300;
	pro = false;
	Color = 2;
}

