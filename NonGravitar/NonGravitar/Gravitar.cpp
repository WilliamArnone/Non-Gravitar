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
	pg.X = ScreenWidth() / 2;
	pg.Y = ScreenHeight() / 2;
	srand((unsigned)time(NULL));
	Pianeta p = Pianeta(ScreenWidth(), ScreenHeight(), 10);
	pianeti.push_back(p);
	for (int i = 0; i < 4; i++) {
		do {
			p = Pianeta(ScreenWidth(), ScreenHeight(), 10);
		} while (checkDistance(pianeti, p) || Collision(pg, p));
		pianeti.push_back(p);
	}
}
bool Gravitar::checkDistance(vector<Pianeta> pianeti, Pianeta p) {
	for (auto &planet : pianeti) {
		if (abs(p.X - planet.X) < (p.Size + planet.Size) || abs(p.Y - planet.Y) < (p.Size + planet.Size)) {
			return  true;
		}
	}
	return false;
}
void Gravitar::enterPlanet(Pianeta *newplanet) {
	pianetaAttivo = newplanet;
	pg.X = ScreenWidth() / 2;
	pg.Y = 5;
	pg.angle = 3.14;
	pg.dy = sqrt(pg.dy*pg.dy + pg.dx*pg.dx);
	pg.dx = 0;
}
void Gravitar::exitPlanet() {
	pg.X = pianetaAttivo->X;
	pg.Y = pianetaAttivo->Y - pianetaAttivo->Size - 2.6;

	pianetaAttivo = NULL;
}

bool Gravitar::carbnear() {
	return false;
}
bool Gravitar::Collision(objGame obj1, objGame obj2) {
	float x1 = obj1.X, y1 = obj1.Y, x2 = obj2.X, y2 = obj2.Y;
	return sqrtf((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)) < (obj1.Size + obj2.Size);
}
bool Gravitar::objCrashing() {
	return false;
}
Pianeta * Gravitar::PlanetLanding() {
	for (auto &pian : pianeti) {
		if (Collision(pg, pian))
			return &pian;
	}
	return NULL;
}
bool Gravitar::isLeaving() {
	return pg.Y < 0;
}

void Gravitar::EraseBullets(vector<Proiettile> &Proiettili) {

	if (Proiettili.size() > 0)
	{
		auto i = remove_if(Proiettili.begin(), Proiettili.end(), [&](Proiettile o) {return (o.X < 1 || o.Y < 1 || o.X >= ScreenWidth() - 1 || o.Y >= ScreenHeight() - 1); });
		if (i != Proiettili.end())
			Proiettili.erase(i);
	}

	for (auto &p : Proiettili)
	{
		if (p.X < pianetaAttivo->Terreno[0].X) {
			auto i = remove_if(Proiettili.begin(), Proiettili.end(), [&](Proiettile o) { return Collision(o, pianetaAttivo->Terreno[0]); });
			if (i != Proiettili.end())
				Proiettili.erase(i);
		}
		/*
		else if (b.x < Base.P[pianetaCorrente].A[AreaCorrente].x[1] && b.x > Base.P[pianetaCorrente].A[AreaCorrente].x[0]) {
			auto i = remove_if(vecBullets.begin(), vecBullets.end(), [&](sSpaceObject o) { return (Collision(Base.P[pianetaCorrente].A[AreaCorrente].x[0], Base.P[pianetaCorrente].A[AreaCorrente].y[0], Base.P[pianetaCorrente].A[AreaCorrente].x[1], Base.P[pianetaCorrente].A[AreaCorrente].y[1], b.x, b.y)); });
			if (i != vecBullets.end())
				vecBullets.erase(i);
		}
		else if (b.x < Base.P[pianetaCorrente].A[AreaCorrente].x[2] && b.x > Base.P[pianetaCorrente].A[AreaCorrente].x[1]) {
			auto i = remove_if(vecBullets.begin(), vecBullets.end(), [&](sSpaceObject o) { return (Collision(Base.P[pianetaCorrente].A[AreaCorrente].x[1], Base.P[pianetaCorrente].A[AreaCorrente].y[1], Base.P[pianetaCorrente].A[AreaCorrente].x[2], Base.P[pianetaCorrente].A[AreaCorrente].y[2], b.x, b.y)); });
			if (i != vecBullets.end())
				vecBullets.erase(i);
		}
		else if (b.x < Base.P[pianetaCorrente].A[AreaCorrente].x[3] && b.x > Base.P[pianetaCorrente].A[AreaCorrente].x[2]) {
			auto i = remove_if(vecBullets.begin(), vecBullets.end(), [&](sSpaceObject o) { return(Collision(Base.P[pianetaCorrente].A[AreaCorrente].x[2], Base.P[pianetaCorrente].A[AreaCorrente].y[2], Base.P[pianetaCorrente].A[AreaCorrente].x[3], Base.P[pianetaCorrente].A[AreaCorrente].y[3], b.x, b.y)); });
			if (i != vecBullets.end())
				vecBullets.erase(i);
		}
		else if (b.x < Base.P[pianetaCorrente].A[AreaCorrente].x[4] && b.x > Base.P[pianetaCorrente].A[AreaCorrente].x[3]) {
			auto i = remove_if(vecBullets.begin(), vecBullets.end(), [&](sSpaceObject o) { return (Collision(Base.P[pianetaCorrente].A[AreaCorrente].x[3], Base.P[pianetaCorrente].A[AreaCorrente].y[3], Base.P[pianetaCorrente].A[AreaCorrente].x[4], Base.P[pianetaCorrente].A[AreaCorrente].y[4], b.x, b.y)); });
			if (i != vecBullets.end())
				vecBullets.erase(i);
		}
		else if (b.x > Base.P[pianetaCorrente].A[AreaCorrente].x[4]) {
			auto i = remove_if(vecBullets.begin(), vecBullets.end(), [&](sSpaceObject o) { return Collision(Base.P[pianetaCorrente].A[AreaCorrente].x[4], Base.P[pianetaCorrente].A[AreaCorrente].y[4], ScreenWidth(), ScreenHeight(), b.x, b.y); });
			if (i != vecBullets.end())
				vecBullets.erase(i);
		}*/
	}

}


void Gravitar::updateTorr(float fElapsedTime) {
	for (auto &t : pianetaAttivo->Torrette) {
		t.Update(fElapsedTime, pg.X, pg.Y);
	}
}
void Gravitar::updateBull(float fElapsedTime) {
	for (auto &p : Proiettili)
		p.Update(fElapsedTime);

	EraseBullets(Proiettili);

}
void Gravitar::updateNav(float fElapsedTime) {

	if (m_keys[VK_LEFT].bHeld || m_keys[VK_RIGHT].bHeld)
		pg.ShipRotate(fElapsedTime, m_keys[VK_LEFT].bHeld);

	if (m_keys[VK_UP].bHeld || m_keys[VK_DOWN].bHeld)
		pg.ShipMove(fElapsedTime, m_keys[VK_UP].bHeld);

	if (m_keys[VK_RETURN].bPressed && pianetaAttivo != NULL)
		Proiettili.push_back({ true, pg.X, pg.Y, pg.angle });

	if (m_keys[VK_SPACE].bHeld) {
		pg.dx = 0;
		pg.dy = 0;
	}

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

void Gravitar::changeArea() {
	bool next = pg.X > ScreenWidth();
	if ((pg.X < 0) || next) {
		pg.X = next ? pg.X = 5 : pg.X = ScreenWidth() - 5;
		pianetaAttivo->areaCorrente += next ? 1 : -1;
		pianetaAttivo->areaCorrente = pianetaAttivo->areaCorrente % pianetaAttivo->Aree.size();
	}
}

bool Gravitar::checkEnd() {
	return false;
}

void Gravitar::reborn() {

}


#pragma region Draw

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
		sx[i] = sx[i] + pg.X;
		sy[i] = sy[i] + pg.Y;
	}

	// Draw Closed Polygon
	for (int i = 0; i < 4; i++)
	{
		int j = i + 1;
		DrawLine(sx[i % 3], sy[i % 3], sx[j % 3], sy[j % 3]);
	}
}

void Gravitar::DrawTorr(Torretta torre) {
	FillTriangle(torre.Xl, torre.Yl, torre.XUp, torre.YUp, torre.Xr, torre.Yr, PIXEL_SOLID, FG_RED);
}

void Gravitar::DrawCarb(Carburante carb) {
	FillCircle(carb.X, carb.Y, 2, PIXEL_SOLID, FG_CYAN);
}
void Gravitar::DrawPlanet(Pianeta planet) {
	FillCircle(planet.X, planet.Y, planet.Size, PIXEL_SOLID, planet.Colore);
}
void Gravitar::DrawBullet(Proiettile bullet) {
	Draw(bullet.X, bullet.Y);
}
void Gravitar::DrawRay() {
	DrawLine(pg.X, pg.Y, pg.X - 5, pg.Y - 10);
	DrawLine(pg.X, pg.Y, pg.X + 5, pg.Y - 10);
}
void Gravitar::DrawArea() {
	int areaCorrente = pianetaAttivo->areaCorrente;
	DrawLine(0, ScreenHeight(), pianetaAttivo->Aree[areaCorrente].Terreno[0].X, pianetaAttivo->Aree[areaCorrente].Terreno[0].Y, PIXEL_SOLID, pianetaAttivo->Colore);
	for (int i = 0; i < pianetaAttivo->Aree[areaCorrente].Terreno.size() - 1; i++)
	{
		DrawLine(pianetaAttivo->Aree[areaCorrente].Terreno[i].X, pianetaAttivo->Aree[areaCorrente].Terreno[i].Y, pianetaAttivo->Aree[areaCorrente].Terreno[i + 1].X, pianetaAttivo->Aree[areaCorrente].Terreno[i + 1].Y, PIXEL_SOLID, pianetaAttivo->Colore);
	}
}
#pragma endregion


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
	pg.Size = 2.5;
	resetGame();

	return true;
}

bool Gravitar::OnUserUpdate(float fElapsedTime) {
	Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, 0);	//Pulise la schermata

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
			if (p != NULL)
				enterPlanet(p);
		}
		if (pianetaAttivo != NULL) {
			//update
			updateBull(fElapsedTime);
			updateTorr(fElapsedTime);

			//collisioni
			CheckCollisions();
			changeArea();
		}
		else {
			WrapCoordinate();
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
			DrawArea();
			Draw(pg.X, pianetaAttivo->Aree[pianetaAttivo->areaCorrente].FindY(pg.X), PIXEL_SOLID, FG_RED);
 			for (auto &b : pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Torrette) {
				DrawTorr(b);
			}
			for (auto &b : pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Carburanti) {
				DrawCarb(b);
			}
			for (auto &b : Proiettili) {
				DrawBullet(b);
			}
		}
	}



	return true;
}