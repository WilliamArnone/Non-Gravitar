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
	vite = 2;
	score = 0;
	pg.fuel = 1000000;
	pg.dx = 0;
	pg.dy = 0;
	pg.angle = 0;
	gameover = false;
}
void Gravitar::newUniverse() {
	pianetaAttivo = NULL;
	pianeti.clear();
	pg.X = ScreenWidth() / 2;
	pg.Y = ScreenHeight() / 2;
	srand((unsigned)time(NULL));
	Pianeta p;
	do {
		p = Pianeta(ScreenWidth(), ScreenHeight()); // il primo pianeta viene generato fuori così che si possa fare il controllo che gli altri non vengano creati attaccati a lui
	} while (Collision(pg, p)); //si controlla che il pianeta non collida con il giocatore all'inizio. Si cicla fino a che questa condizione non è rispettata 
	pianeti.push_back(p);
	for (int i = 0; i < 4; i++) {
		do {
			p = Pianeta(ScreenWidth(), ScreenHeight());
		} while (checkDistance(pianeti, p) || Collision(pg, p)); //si controlla che il pianeta non collida con il giocatore all'inizio e neanche con gli altri pianeti. Si cicla fino a che questa condizione non è rispettata
		pianeti.push_back(p);
	}
}
bool Gravitar::checkDistance(vector<Pianeta> pianeti, Pianeta p) {
	for (auto &planet : pianeti) {
		if (abs(p.X - planet.X) < (p.Size + planet.Size) || abs(p.Y - planet.Y) < (p.Size + planet.Size)) { //si controlla per ogni pianeta che non collida con gli altri. In caso succeda si ritorna true
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
	pg.dy = sqrt(pg.dy*pg.dy + pg.dx*pg.dx)/2;
	pg.dx = 0;
}
void Gravitar::exitPlanet() {
	pg.X = pianetaAttivo->X;
	pg.Y = pianetaAttivo->Y - pianetaAttivo->Size - 2.6;

	pianetaAttivo = NULL;
}

void Gravitar::carbnear() {
	int i = 0;
	for (auto &c : pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Carburanti)
	{
		float dx = (c.Y-pg.Y);
		if ((c.Y > pg.Y) && (c.Y < pg.Y + 10) && (c.X < pg.X + dx) && (c.X > pg.X - dx)) {
			pg.fuel += c.pro? 200 : 100;
		}

		pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Carburanti.erase(pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Carburanti.begin() + i);

		i++;
	}
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
}

void Gravitar::updateTorr(float fElapsedTime) {
	for (auto &t : pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Torrette) {
		if (t.pro)
			((TorrettaPro*)&t)->UpdatePro(fElapsedTime, pg.X, pg.Y);
		else
			t.Update(fElapsedTime, pg.X, pg.Y);

		if (t.list.size() > 0)
			Proiettili.insert(Proiettili.begin(), t.list.begin(), t.list.end());
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

	if (m_keys[VK_SPACE].bPressed && pianetaAttivo != NULL)
		Proiettili.push_back({ true, pg.X, pg.Y, pg.angle });

	if (m_keys[VK_RETURN].bHeld) {
		rayOn = true;
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
		Proiettili.clear();
	}
}

bool Gravitar::checkEnd() {
	return false;
}

void Gravitar::reborn() {
	vite--;
	pianetaAttivo = NULL;
	pg.X = ScreenWidth() / 2;
	pg.Y = ScreenHeight() / 2;
	pg.dx = 0;
	pg.dy = 0;
	pg.angle = 0;
	morto = false;
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
	auto color = torre.pro ? FG_RED : FG_WHITE;
	float mx[3] = { 0.0f, -2.5f, +2.5f };
	float my[3] = { -4.0f, +2.5f, +2.5f };
	float sx[3], sy[3];

	// Rotate
	for (int i = 0; i < 3; i++)
	{
		sx[i] = mx[i] * cosf(torre.angle) - my[i] * sinf(torre.angle);
		sy[i] = mx[i] * sinf(torre.angle) + my[i] * cosf(torre.angle);
	}

	// Translate
	for (int i = 0; i < 3; i++)
	{
		sx[i] = sx[i] + torre.X;
		sy[i] = sy[i] + torre.Y;
	}
	
	FillTriangle(sx[0], sy[0], sx[1], sy[1], sx[2], sy[2], PIXEL_SOLID, color);
}

void Gravitar::DrawCarb(Carburante carb) {
	if (carb.pro)
		FillCircle(carb.X, carb.Y, carb.Size, PIXEL_SOLID, FG_CYAN);
	else
		FillCircle(carb.X, carb.Y, carb.Size, PIXEL_SOLID, FG_DARK_YELLOW);
}

void Gravitar::DrawPlanet(Pianeta planet) {
	FillCircle(planet.X, planet.Y, planet.Size, PIXEL_SOLID, planet.Colore);
}
void Gravitar::DrawBullet(Proiettile bullet) {
	Draw(bullet.X, bullet.Y);
}
void Gravitar::DrawRay() {
	DrawLine(pg.X, pg.Y, pg.X - 5, pg.Y + 10, PIXEL_THREEQUARTERS,FG_CYAN);
	DrawLine(pg.X, pg.Y, pg.X + 5, pg.Y + 10, PIXEL_THREEQUARTERS, FG_CYAN);
}
void Gravitar::DrawArea() {
	int areaCorrente = pianetaAttivo->areaCorrente; //quando esiste il pianeta attivo viene presa l'area in cui il giocatore si trova e ne vengono disegnati tutti i punti
	for (int i = 0; i < pianetaAttivo->Aree[areaCorrente].Terreno.size() - 1; i++)
	{
		DrawLine(pianetaAttivo->Aree[areaCorrente].Terreno[i].X, pianetaAttivo->Aree[areaCorrente].Terreno[i].Y, pianetaAttivo->Aree[areaCorrente].Terreno[i + 1].X, pianetaAttivo->Aree[areaCorrente].Terreno[i + 1].Y, PIXEL_SOLID, pianetaAttivo->Colore);
	}
}
void Gravitar::DrawTitle() {
	// pulsanti
	//->
	DrawLine(150, 90, 150, 96);
	DrawLine(150, 90, 156, 90);
	DrawLine(156, 96, 150, 96);
	DrawLine(156, 96, 156, 90);
	DrawLine(151, 93, 154, 93);
	DrawLine(154, 93, 152, 91);
	DrawLine(154, 93, 152, 95);

	//<-
	DrawLine(130, 90, 130, 96);
	DrawLine(130, 90, 136, 90);
	DrawLine(136, 96, 130, 96);
	DrawLine(136, 96, 136, 90);
	DrawLine(132, 93, 135, 93);
	DrawLine(132, 93, 134, 91);
	DrawLine(132, 93, 134, 95);

	//giù
	DrawLine(140, 90, 140, 96);
	DrawLine(140, 90, 146, 90);
	DrawLine(146, 96, 140, 96);
	DrawLine(146, 96, 146, 90);
	DrawLine(143, 90, 143, 94);
	DrawLine(143, 94, 141, 92);
	DrawLine(143, 94, 145, 92);

	//^
	DrawLine(140, 80, 140, 86);
	DrawLine(140, 80, 146, 80);
	DrawLine(146, 86, 140, 86);
	DrawLine(146, 86, 146, 80);
	DrawLine(143, 82, 143, 86);
	DrawLine(143, 82, 141, 84);
	DrawLine(143, 82, 145, 84);

	DrawString(140, 75, L"Move");
	DrawString(ScreenWidth() / 2 - 8, ScreenHeight() / 2 + 35, L"Press TAB to start");
}

void Gravitar::DrawGameOver() {
	//G
	DrawLine(66, 45, 56, 45);
	DrawLine(66, 45, 66, 38);
	DrawLine(56, 45, 56, 25);
	DrawLine(66, 25, 56, 25);
	DrawLine(66, 38, 61, 38);

	//A
	DrawLine(78, 45, 74, 25);
	DrawLine(74, 25, 70, 45);
	DrawLine(76, 38, 72, 38);

	//M
	DrawLine(82, 25, 87, 35);
	DrawLine(82, 45, 82, 25);
	DrawLine(87, 35, 92, 25);
	DrawLine(92, 45, 92, 25);

	//E
	DrawLine(96, 45, 96, 25);
	DrawLine(96, 45, 104, 45);
	DrawLine(96, 25, 104, 25);
	DrawLine(96, 35, 104, 35);

	//O
	DrawLine(66, 75, 57, 75);
	DrawLine(66, 75, 66, 55);
	DrawLine(57, 75, 57, 55);
	DrawLine(66, 55, 57, 55);

	//V
	DrawLine(78, 55, 74, 75);
	DrawLine(74, 75, 70, 55);

	//E
	DrawLine(82, 75, 82, 55);
	DrawLine(82, 75, 91, 75);
	DrawLine(82, 55, 91, 55);
	DrawLine(82, 65, 91, 65);

	//R
	DrawLine(95, 75, 95, 55);
	DrawLine(95, 55, 103, 55);
	DrawLine(103, 55, 103, 65);
	DrawLine(95, 65, 103, 65);
	DrawLine(95, 65, 103, 75);

	DrawString(ScreenWidth() / 2 - 5, ScreenHeight() / 2 + 35, L"Score: " + to_wstring(score));
}

#pragma endregion



void Gravitar::CheckCollisions() {
	if (pianetaAttivo != NULL) {
		objGame terr = objGame(pg.X, pianetaAttivo->Aree[pianetaAttivo->areaCorrente].FindY(pg.X), 0);
		if (Collision(pg, terr)) {
			morto = true;
		}
		for (auto &b : Proiettili) {
			if (Collision(pg, b) && !b.player) {
				morto = true;
				Proiettili.clear();
			}
		}
		int indiceT = 0;
		for (auto &t : pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Torrette) {
			for (auto &b : Proiettili) {
 				if (Collision(t, b) && b.player) {
					//??????
					pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Torrette.erase(pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Torrette.begin()+indiceT);
				}
			}
			indiceT++;
		}
		for (auto &b : Proiettili) {
			terr.X = b.X;
			terr.Y = pianetaAttivo->Aree[pianetaAttivo->areaCorrente].FindY(b.X);
			if (Collision(b, terr))
			{
				b.X = -1000;
			}
		}
	}
}


bool Gravitar::OnUserCreate() {
	pg.Size = 2.5;
	morto = false;
	gameover = true;
	//resetGame();
	return true;

}

bool Gravitar::OnUserUpdate(float fElapsedTime) {
	Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, 0);	//Pulise la schermata
	rayOn=false;

	if (m_keys[VK_TAB].bHeld) {
		resetGame();
	}

	if (checkEnd()) {
		gameover = true;
	}
	else {
		if (morto) {
			if (vite == 0)
				gameover = true;
			else
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
			if (rayOn)
				carbnear();
		}
		else {
			WrapCoordinate();
		}
	}

	//disegno

	if (gameover) {
		if (morto)
			DrawGameOver();
		else
			DrawTitle();
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
			if (rayOn)
				DrawRay();
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
		DrawString(2, 2, L"Life: " + to_wstring(vite));
		DrawString(2, 4, L"Fuel: " + to_wstring(pg.fuel));
		DrawString(2, 6, L"Score: " + to_wstring(score));
	}

	return true;
}