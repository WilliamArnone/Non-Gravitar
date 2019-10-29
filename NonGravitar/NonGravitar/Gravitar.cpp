	#include "Gravitar.hpp"


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
	pg.fuel = 10000;
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
	pg.dy = sqrt(pg.dy*pg.dy + pg.dx*pg.dx) / 2;
	pg.dx = 0;
}
void Gravitar::exitPlanet() {
	pg.X = pianetaAttivo->X;
	pg.Y = pianetaAttivo->Y - pianetaAttivo->Size - 2.6;

	pianetaAttivo = NULL;
}

/*Controlla se il raggio traente può succhiare un fuel, se si lo rimuove e lo aggiunge al pg.fuel*/
void Gravitar::carbnear() {
	auto i = remove_if(pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Carburanti.begin(), pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Carburanti.end(), [&](Carburante c)
	{
		float dx = (c.Y - pg.Y);
		if ((c.Y > pg.Y) && (c.Y < pg.Y + 10) && (c.X < pg.X + dx) && (c.X > pg.X - dx)) {
			pg.fuel += c.pro ? 4000 : 2000;
			score += c.pro ? 100 : 50;
			return true;
		}
		else
			return false;
	});

	if (i != pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Carburanti.end())
		pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Carburanti.erase(i);
}

bool Gravitar::Collision(objGame obj1, objGame obj2) {
	float x1 = obj1.X, y1 = obj1.Y, x2 = obj2.X, y2 = obj2.Y;
	return sqrtf((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)) < (obj1.Size + obj2.Size);
}


Pianeta * Gravitar::PlanetLanding() {
	for (auto &pian : pianeti) {
		if (Collision(pg, pian))
			return &pian;
	}
	return NULL;
}


void Gravitar::EraseBullets(vector<Proiettile> &Proiettili) {
	if (Proiettili.size() > 0)
	{
		auto i = remove_if(Proiettili.begin(), Proiettili.end(), [&](Proiettile o) {return (o.X < 1 || o.Y < 1 || o.X >= ScreenWidth() - 1 || o.Y >= ScreenHeight() - 1); });
		if (i != Proiettili.end())
			Proiettili.erase(i);
	}
}

#pragma region Updates

void Gravitar::updateTorr(float fElapsedTime) {
	for (auto &t : pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Torrette) {
		if (t.pro)
			((TorrettaPro*)&t)->UpdatePro(fElapsedTime, pg.X, pg.Y);
		else
			t.Update(fElapsedTime, pg.X, pg.Y);

		if (t.TorreProiettili.size() > 0)
			Proiettili.insert(Proiettili.begin(), t.TorreProiettili.begin(), t.TorreProiettili.end());
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
		Proiettili.push_back({ true,(-(-5.5f * sinf(pg.angle))) + pg.X,  (-5.5f * cosf(pg.angle)) + pg.Y, pg.angle });

	if (m_keys[VK_RETURN].bHeld) {
		rayOn = true;
	}
	//Velocità finale
	pg.X += pg.dx * fElapsedTime;
	pg.Y += pg.dy * fElapsedTime;

}

#pragma endregion

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
		pianetaAttivo->areaCorrente += pianetaAttivo->Aree.size() + (next ? +1 : -1);
		pianetaAttivo->areaCorrente = pianetaAttivo->areaCorrente % pianetaAttivo->Aree.size();
		Proiettili.clear();
	}
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
	Proiettili.clear();
}

#pragma region Draw
/*Vengono richiamate tutte le funzioni necessarie per disegnare il mondo generato e l'astronave*/

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

	FillTriangle(sx[0], sy[0], sx[1], sy[1], sx[2], sy[2], PIXEL_SOLID, torre.Color);
}

void Gravitar::DrawCarb(Carburante carb) {
	int color = carb.pro ? FG_CYAN : FG_DARK_YELLOW;
	FillCircle(carb.X, carb.Y, carb.Size, PIXEL_SOLID, color);
}

void Gravitar::DrawPlanet(Pianeta planet) {
	FillCircle(planet.X, planet.Y, planet.Size, PIXEL_SOLID, planet.Colore);
}

void Gravitar::DrawBullet(Proiettile bullet) {
	Draw(bullet.X, bullet.Y,PIXEL_SOLID,bullet.Color);
}

void Gravitar::DrawRay() {
	DrawLine(pg.X, pg.Y, pg.X - 5, pg.Y + 10, PIXEL_THREEQUARTERS, FG_CYAN);
	DrawLine(pg.X, pg.Y, pg.X + 5, pg.Y + 10, PIXEL_THREEQUARTERS, FG_CYAN);
}

void Gravitar::DrawArea() {
	//quando esiste il pianeta attivo viene presa l'area in cui il giocatore si trova e ne vengono disegnati tutti i punti
	int areaCorrente = pianetaAttivo->areaCorrente;

	for (int i = 0; i < pianetaAttivo->Aree[areaCorrente].Terreno.size() - 1; i++)
		DrawLine(pianetaAttivo->Aree[areaCorrente].Terreno[i].X, pianetaAttivo->Aree[areaCorrente].Terreno[i].Y, pianetaAttivo->Aree[areaCorrente].Terreno[i + 1].X, pianetaAttivo->Aree[areaCorrente].Terreno[i + 1].Y, PIXEL_SOLID, pianetaAttivo->Colore);
}
void Gravitar::DrawTitle(float fElapsedTime) {
	//titolo

	//(
	Draw(68, 21);
	DrawLine(67, 20, 67, 15);
	Draw(68, 14);

	//N
	DrawLine(71, 20, 71, 15);
	DrawLine(71, 15, 75, 20);
	DrawLine(75, 20, 75, 15);

	//O
	DrawLine(78, 20, 78, 15);
	DrawLine(78, 20, 82, 20);
	DrawLine(78, 15, 82, 15);
	DrawLine(82, 15, 82, 20);

	//N
	DrawLine(85, 20, 85, 15);
	DrawLine(85, 15, 89, 20);
	DrawLine(89, 20, 89, 15);

	//)
	Draw(92, 21);
	DrawLine(93, 20, 93, 15);
	Draw(92, 14);






	//G
	DrawLine(48, 45, 38, 45);
	DrawLine(48, 45, 48, 38);
	DrawLine(38, 45, 38, 25);
	DrawLine(48, 25, 38, 25);
	DrawLine(48, 38, 43, 38);

	//R
	DrawLine(51, 45, 51, 25);
	DrawLine(51, 25, 59, 25);
	DrawLine(59, 25, 59, 35);
	DrawLine(51, 35, 59, 35);
	DrawLine(51, 35, 59, 45);

	//A
	DrawLine(70, 45, 66, 25);
	DrawLine(66, 25, 62, 45);
	DrawLine(68, 38, 64, 38);


	//V
	DrawLine(80, 25, 76, 45);
	DrawLine(76, 45, 72, 25);

	//I
	DrawLine(84, 25, 84, 45);

	//T
	DrawLine(87, 25, 98, 25);
	DrawLine(93, 45, 93, 25);

	//A
	DrawLine(106, 45, 102, 25);
	DrawLine(102, 25, 98, 45);
	DrawLine(104, 38, 100, 38);

	//R
	DrawLine(109, 45, 109, 25);
	DrawLine(109, 25, 117, 25);
	DrawLine(117, 25, 117, 35);
	DrawLine(109, 35, 117, 35);
	DrawLine(109, 35, 117, 45);


	// pulsanti
	//->
	DrawLine(30, 90, 30, 96);
	DrawLine(30, 90, 36, 90);
	DrawLine(36, 96, 30, 96);
	DrawLine(36, 96, 36, 90);
	DrawLine(31, 93, 34, 93);
	DrawLine(34, 93, 32, 91);
	DrawLine(34, 93, 32, 95);

	//<-
	DrawLine(10, 90, 10, 96);
	DrawLine(10, 90, 16, 90);
	DrawLine(16, 96, 10, 96);
	DrawLine(16, 96, 16, 90);
	DrawLine(12, 93, 15, 93);
	DrawLine(12, 93, 14, 91);
	DrawLine(12, 93, 14, 95);

	//giù
	DrawLine(20, 90, 20, 96);
	DrawLine(20, 90, 26, 90);
	DrawLine(26, 96, 20, 96);
	DrawLine(26, 96, 26, 90);
	DrawLine(23, 90, 23, 94);
	DrawLine(23, 94, 21, 92);
	DrawLine(23, 94, 25, 92);

	//^
	DrawLine(20, 80, 20, 86);
	DrawLine(20, 80, 26, 80);
	DrawLine(26, 86, 20, 86);
	DrawLine(26, 86, 26, 80);
	DrawLine(23, 82, 23, 86);
	DrawLine(23, 82, 21, 84);
	DrawLine(23, 82, 25, 84);

	// spazio
	DrawLine(60, 95, 100, 95);
	DrawLine(60, 90, 100, 90);
	DrawLine(60, 95, 60, 90);
	DrawLine(100, 95, 100, 90);

	//invio
	DrawLine(150, 95, 150, 75);
	DrawLine(150, 75, 140, 75);
	DrawLine(140, 75, 140, 81);
	DrawLine(140, 81, 143, 81);
	DrawLine(143, 81, 143, 95);
	DrawLine(143, 95, 150, 95);

	blink -= fElapsedTime;
	if (blink < 0.5f) {
		DrawString(ScreenWidth() / 2 - 8, ScreenHeight() / 2 + 10, L"Press TAB to start ");
	}
	if (blink<=0){
		blink = 1.0f;
	}

	DrawString(15, 75, L"Move with Arrows");
	DrawString(ScreenWidth() / 2 - 9, ScreenHeight() / 2 + 35, L"Press Space to shoot");
	DrawString(132,72, L"Press Enter to use the ray");
}

void Gravitar::DrawGameOver(float fElapsedTime) {
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


	blink -= fElapsedTime;
	if (blink < 0.5f) {
		DrawString(ScreenWidth() / 2 - 9, ScreenHeight() / 2 + 30, L"Press TAB to start ");
	}
	if (blink <= 0) {
		blink = 1.0f;
	}

	DrawString(ScreenWidth() / 2 - 5, ScreenHeight() / 2 + 35, L"Score: " + to_wstring(score));
}

#pragma endregion

/*Controlla le varie collisioni che possono avvenire su schermo, testata e debuggata, ora sicura al 30% !*/
void Gravitar::CheckCollisions() {
	//Controlla le collisioni solo se si è in un pianeta
	if (pianetaAttivo != NULL && !morto) {
		//Collisione Terreno-Astronave
		objGame terr = objGame(pg.X, pianetaAttivo->Aree[pianetaAttivo->areaCorrente].FindY(pg.X), 0);
		if (Collision(pg, terr)) {
			Proiettili.clear();
			morto = true;
		}
		//Collisione Proiettile-Astronave
		for (auto &b : Proiettili) {
			if (Collision(pg, b) && !b.player) {
				Proiettili.clear();
				morto = true;
			}
		}
		//Collisione Proiettile-Torretta
		for (auto &p : Proiettili) {
		int IndiceT=0;
			for (auto &t : pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Torrette) {
				if (Collision(p,t)) {
					score += (t.pro)? 500 : 100;
					pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Torrette.erase(pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Torrette.begin()+IndiceT);
				}
				IndiceT++;
			}
		}
		//Collisione Proiettile-Terreno
		for (auto &b : Proiettili) {
			terr.X = b.X;
			terr.Y = pianetaAttivo->Aree[pianetaAttivo->areaCorrente].FindY(b.X);
			if (Collision(b, terr))
				b.X = -1000;
		}
	}
}

/*Creazione dell'astronave denominata pg, 18 STR*/
bool Gravitar::OnUserCreate() {
	blink = 1.0f;
	pg.Size = 2.5;
	pg.fuel = 10000;
	morto = false;
	gameover = true;
	return true;

}

bool Gravitar::OnUserUpdate(float fElapsedTime) {
	Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, 0);	//Pulise la schermata
	rayOn = false;
	/*Reset Game*/
	if (m_keys[VK_TAB].bHeld) {
		resetGame();
	}

	/*Se il gioco è finito, crea un nuovo universo*/
	if (pianeti.size() <= 0)
	{
		newUniverse();
		score += 10000;
	}

	else {

		if (morto) {
			if (vite == 0)
				gameover = true;
			else
				reborn();
		}
		if (pg.fuel <= 0) {
			gameover = true;
			morto = true;
		}

		updateNav(fElapsedTime);

		/*Controlla i pianeti, quelli morti li rimuove dall'elenco e posiziona il giocatore nel mezzo dell'universo*/
		auto i = remove_if(pianeti.begin(), pianeti.end(), [&](Pianeta P) {return P.isEnded(); });
		if (i != pianeti.end())
		{
			pianeti.erase(i);
			pianetaAttivo = NULL;
			pg.X = ScreenWidth() / 2;
			pg.Y = ScreenHeight() / 2;
			pg.dx = 0;
			pg.dy = 0;
			score += 1000;
			Proiettili.clear();
		}

		/*l'astronave esce dall' atmosfera*/
		if (pianetaAttivo != NULL && pg.Y < 0) {
			Proiettili.clear();
			exitPlanet();
		}

		/*l'astronave entra nell'atmosfera*/
		else if (pianetaAttivo == NULL) {
			Pianeta *p = PlanetLanding();
			if (p != NULL)
				enterPlanet(p);
		}

		/*Se si è in un pianeta, si fa l'update dei vari objGame*/
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

	/*Se il giocatore è morto o è appena spawnato, gli mostra una schermata di gameover o benvenuto*/
	if (gameover) {
		if (morto) {
			DrawGameOver(fElapsedTime);
		}
		else {
			DrawTitle(fElapsedTime);
		}
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
		//Stampa a schermo i valori che il giocatore deve sapere
		DrawString(2, 2, L"Life: " + to_wstring(vite + 1));
		DrawString(2, 4, L"Fuel: " + to_wstring(pg.fuel));
		DrawString(2, 6, L"Score: " + to_wstring(score));

	}

	return true;
}