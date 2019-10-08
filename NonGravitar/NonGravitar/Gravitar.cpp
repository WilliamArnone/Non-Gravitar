#include "Gravitar.h"


Gravitar::Gravitar()
{
	m_sAppName = L"Non-Gravitar";
}


Gravitar::~Gravitar()
{
}


void Gravitar::resetGame() {
	newUniverse();
	score = 0;
	pg.fuel = 1000000;
	pg.dx = 0;
	pg.dy = 0;
	gameover = false;
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
	pg.X = ScreenWidth() / 2;
	pg.Y = ScreenHeight() / 2;
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
	if (m_keys[VK_LEFT].bHeld || m_keys[VK_RIGHT].bHeld)
		pg.ShipRotate(fElapsedTime, m_keys[VK_LEFT].bHeld);

	if (m_keys[VK_UP].bHeld || m_keys[VK_DOWN].bHeld)
		pg.ShipMove(fElapsedTime, m_keys[VK_UP].bHeld);


	//Velocità finale
	pg.X += pg.dx * fElapsedTime;
	pg.Y += pg.dy * fElapsedTime;

}

void Gravitar::clear() {

}
void Gravitar::WrapCoordinate() {
	if (pg.X < 0.0f)	pg.X += (float)ScreenWidth();
	if (pg.X >= (float)ScreenWidth())	pg.X -= (float)ScreenWidth();
	if (pg.Y < 0.0f)	pg.Y += (float)ScreenHeight();
	if (pg.Y >= (float)ScreenHeight()) pg.Y -= (float)ScreenHeight();
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
		sx[i] = mx[i] * cosf(pg.angle) - my[i] * sinf(pg.angle);
		sy[i] = mx[i] * sinf(pg.angle) + my[i] * cosf(pg.angle);
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
	Fill(torre.X - 2, torre.Y + 4, torre.X + 2, torre.Y - 4, PIXEL_SOLID, FG_YELLOW);
}
void Gravitar::DrawCarb(Carburante carb) {
	Fill(carb.X - 2, carb.Y + 2, carb.X + 2, carb.Y - 2);
}
void Gravitar::DrawPlanet(Pianeta planet) {
	FillCircle(planet.X, planet.Y, planet.Size, PIXEL_SOLID, planet.Colore);
}
void Gravitar::DrawBullet(Proiettile bullet) {
	Draw(bullet.X, bullet.Y);
}
void Gravitar::DrawRay() {
	DrawLine(pg.X, pg.Y, pg.X-5, pg.Y-10);
	DrawLine(pg.X, pg.Y, pg.X+5, pg.Y-10);
}

void Gravitar::DrawGameOver() {

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
	resetGame();
	return true;
}

bool Gravitar::OnUserUpdate(float fElapsedTime) {
	Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, 0);

	if (checkEnd()) {				//calcolo dello stato del gioco
		gameover = true;
	}
	else {
		if (morto) {
			reborn();
		}

		updateNav(fElapsedTime);

		if (pianetaAttivo != NULL && isLeaving()) {
			exitPlanet();
		}
		else if (pianetaAttivo == NULL) {
			Pianeta *p = PlanetLanding();
			if(p != NULL)
				enterPlanet(p);
		}						
		if (pianetaAttivo!=NULL) {
			updateBull(fElapsedTime);
			updateTorr(fElapsedTime);
		}
		else {
			WrapCoordinate();
		}
	}

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