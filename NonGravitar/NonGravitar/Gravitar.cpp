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
	pianeti.push_back(Pianeta(ScreenWidth(), ScreenHeight()));
	for (int i = 1; i < 5; i++) {
		
		Pianeta p = Pianeta(ScreenWidth(), ScreenHeight());

		bool canAdd = false;
		for (auto &planet : pianeti) {
			if (!canAdd) {
				canAdd = !Collision(p, planet);
			}
		}

		if (canAdd)
			pianeti.push_back(Pianeta(ScreenWidth(), ScreenHeight()));
		else
			i--;
	}
}

void Gravitar::enterPlanet(Pianeta *newplanet) {

}
void Gravitar::exitPlanet() {

}

bool Gravitar::carbnear() {
	return false;
}
bool Gravitar::Collision(objGame obj1, objGame obj2) {
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

Pianeta * Gravitar::checkPlanet() {
	return new Pianeta();
}

void Gravitar::updateTorr(float fElapsedTime) {

}
void Gravitar::updateBull(float fElapsedTime) {

}
void Gravitar::updateNav(float fElapsedTime) {

}

void Gravitar::clear() {

}
bool Gravitar::checkEnd() {
	return false;
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

void Gravitar::DrawGameOver() {

}

void Gravitar::ResetGame() {

}




bool Gravitar::OnUserCreate() {

	return true;
}

bool Gravitar::OnUserUpdate(float fElapsedTime) {

	if (checkEnd()) {				//calcolo dello stato del gioco
		gameover = true;
	}
	else {
		if (morto) {
			reborn();
		}
		if (pianetaAttivo != NULL && isLeaving()) {
			exitPlanet();
		}
		else if (pianetaAttivo == NULL && isLanding()) {
			Pianeta *p = checkPlanet();
			enterPlanet(p);
		}
		updateNav(fElapsedTime);		//e stato della tastiera
										//male che vada, aggiungere qui
		if (pianetaAttivo!=NULL) {
			updateBull(fElapsedTime);
			updateTorr(fElapsedTime);
			
		}
	}


	//disegno

	if (gameover) {
		DrawGameOver();
	}
	else {
		DrawNav();
		if (pianetaAttivo == NULL) {
			for (auto &b : pianeti) {
				DrawPlanet(b);
			}
		}
		else {
			//for(auto &b : pianetaAttivo->torrette){
			//DrawTorr(b);
			//}
			//for(auto &b : pianetaAttivo->carburanti){
			//DrawCarb(b);
			//}
			for (auto &b : proiettili) {
				DrawBullet(b);
			}
		}
	}



	return true;
}