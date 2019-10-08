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
	srand((unsigned)time(NULL));
	Pianeta p=Pianeta(ScreenWidth(), ScreenHeight());
	pianeti.push_back(p);
	for (int i = 0; i < 4; i++) {
		do {
			p = Pianeta(ScreenWidth(), ScreenHeight());
		} while (checkDistance(pianeti, p));
		pianeti.push_back(p);
	}
}
bool Gravitar::checkDistance(vector<Pianeta> pianeti, Pianeta p) {
	for(auto &planet: pianeti){
		if (abs(p.X - planet.X) < (p.Size + planet.Size) || abs(p.Y - planet.Y) < (p.Size + planet.Size)) {
			return  true;
		}
	}
	return false;
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
Pianeta * Gravitar::PlanetLanding() {
	return NULL;
}
bool Gravitar::isLeaving() {
	return false;
}

void Gravitar::updateTorr(float fElapsedTime) {
	for (auto &t : pianetaAttivo->Torrette) {
		t.Update(fElapsedTime);
	}
}
void Gravitar::updateBull(float fElapsedTime) {
	for (auto &p : Proiettili) {
		p.Update(fElapsedTime);
	}
}
void Gravitar::updateNav(float fElapsedTime) {
	//pg.ShipMove(fElapsedTime, m_keys);
}

void Gravitar::clear() {

}
bool Gravitar::checkEnd() {
	return false;
}

void Gravitar::reborn() {

}

void Gravitar::DrawNav() {

	float mx[3] = { 0.0f, -2.5f, +2.5f };
	float my[3] = { -5.5f, +2.5f, +2.5f };
	float sx[3], sy[3];

	// Rotate
	for (int i = 0; i < 3; i++)
	{
		sx[i] = mx[i] * cosf(pg.Angle) - my[i] * sinf(pg.Angle);
		sy[i] = mx[i] * sinf(pg.Angle) - my[i] * cosf(pg.Angle);
	}

	// Translate
	for (int i = 0; i < 3; i++)
	{
		sx[i] = sx[i]+pg.X;
		sy[i] = sy[i]+pg.Y;
	}

	// Draw Closed Polygon
	for (int i = 0; i < 4; i++)
	{
		int j = i + 1;
		DrawLine(sx[i % 3], sy[i % 3], sx[j % 3], sy[j % 3]);
	}
}
void Gravitar::DrawTorr(Torretta torre) {

}
void Gravitar::DrawCarb(Carburante carb) {

}
void Gravitar::DrawPlanet(Pianeta planet) {
	FillCircle(planet.X, planet.Y, planet.Size, planet.Colore, planet.Colore);
}
void Gravitar::DrawBullet(Proiettile bullet) {

}
void Gravitar::DrawRay() {

}

void Gravitar::DrawGameOver() {

}

void Gravitar::ResetGame() {

}

void Gravitar::CheckCollisions() {
	if (pianetaAttivo != NULL) {
		for (auto &b : Proiettili) {
			if (Collision(pg, b)) {
				//morto
			}
		}
		for (auto &t : pianetaAttivo->Torrette) {
			for (auto &b : Proiettili) {
				if (Collision(t, b)) {
					//eliminare torretta
				}
			}
		}
	}
}


bool Gravitar::OnUserCreate() {
	newUniverse();
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
		else if (pianetaAttivo == NULL) {
			Pianeta *p = PlanetLanding();
			if(p != NULL)
				enterPlanet(p);
		}

		updateNav(fElapsedTime);
										
		if (pianetaAttivo!=NULL) {
			updateBull(fElapsedTime);
			updateTorr(fElapsedTime);
		}
	}


	//Da controllare Collisioni
	CheckCollisions();

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
			for(auto &b : pianetaAttivo->Torrette){
				DrawTorr(b);
			}
			for(auto &b : pianetaAttivo->Carburanti){
				DrawCarb(b);
			}
			for (auto &b : Proiettili) {
				DrawBullet(b);
			}
		}
	}



	return true;
}