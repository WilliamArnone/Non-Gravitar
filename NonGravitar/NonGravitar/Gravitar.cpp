#include "Gravitar.h"



Gravitar::Gravitar()
{
	m_sAppName = L"Non-Gravitar";
}


Gravitar::~Gravitar()
{
}


void Gravitar::resetGame() {

}

void Gravitar::newUniverse() {

}

void Gravitar::enterPlanet(Pianeta *newplanet) {

}
void Gravitar::exitPlanet() {

}

bool Gravitar::carbnear() {
	return false;
}
bool Gravitar::bulletcollision(objGame oggetto, Proiettile bullet) {
	return false;
}
bool Gravitar::objCrashing() {
	return false;
}
bool Gravitar::isLanding() {
	return false;
}
bool Gravitar::isLeaving() {
	return false;
}

void Gravitar::updateTorr() {

}
void Gravitar::updateBull() {

}
void Gravitar::updateNav() {

}

void Gravitar::clear() {

}
bool Gravitar::checkEnd() {
	return false;
}

void Gravitar::gameover() {

}
void Gravitar::reborn() {

}

void Gravitar::DrawNav() {

}
void Gravitar::DrawTorr(Torretta torre) {

}
void Gravitar::DrawCarb(Carburante carb) {

}
void Gravitar::DrawPlanet(Pianeta planet) {

}
void Gravitar::DrawBullet(Proiettile bullet) {

}
void Gravitar::DrawRay() {

}

void Gravitar::ResetGame() {

}




bool Gravitar::OnUserCreate() {

	return true;
}

bool Gravitar::OnUserUpdate(float fElapsedTime) {

	return true;
}