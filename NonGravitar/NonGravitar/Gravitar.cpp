#include "Gravitar.hpp"

Gravitar::Gravitar()
{
	m_sAppName = L"Non-Gravitar";
}

Gravitar::~Gravitar()
{
}

#pragma region EXEC

void Gravitar::resetGame() {
	//viene resettato il gioco, creando un nuovo universo, resettando vite, carburante e velocità/angolo navicella
	newUniverse();
	vite = 2;
	score = 0;
	pg.fuel = 10000;
	gameover = false;
	morto = false;
}

void Gravitar::resetPG() {
	pg.X = ScreenWidth() / 2;
	pg.Y = ScreenHeight() / 2;
	pg.dx = 0;
	pg.dy = 0;
	pg.angle = 0;
}

void Gravitar::newUniverse() {
	// il nuovo universo viene creato resettando la posizione ed eliminando i pianeti precedenti e resettando la posizione
	pianetaAttivo = NULL;
	pianeti.clear();
	resetPG();
	srand((unsigned)time(NULL));
	//si creano i pianeti
	Pianeta p;
	do {
		// il primo pianeta viene generato fuori così che si possa fare il controllo che gli altri non vengano creati attaccati a lui
		p = Pianeta(ScreenWidth(), ScreenHeight());
	} //si controlla che il pianeta non collida con il giocatore all'inizio. Si cicla fino a che questa condizione non è rispettata 
	while (Collision(pg, p));
	pianeti.push_back(p);
	for (int i = 0; i < 4; i++) {
		do {
			p = Pianeta(ScreenWidth(), ScreenHeight());
		} //si controlla che il pianeta non collida con il giocatore all'inizio e neanche con gli altri pianeti. Si cicla fino a che questa condizione non è rispettata 
		while (checkDistance(p) || Collision(pg, p));
		pianeti.push_back(p);
	}
}

void Gravitar::reborn() {
	//si diminuiscono le vite, si toglie la condizione di morte, si svuota il puntatore al pianeta corrente e si resettano le coordinate della navicella poi si libera il vector di proiettili
	vite--;
	pianetaAttivo = NULL;
	resetPG();
	morto = false;
	Proiettili.clear();
}

void Gravitar::enterPlanet(Pianeta *newplanet) {
	//viene inizializzato il puntatore al pianeta attivo e si setta la posizione del giocatore in mezzo alla schermata in alto con l'angolo in basso
	pianetaAttivo = newplanet;
	pg.X = ScreenWidth() / 2;
	pg.Y = 5;
	pg.angle = 3.14;
	pg.dy = sqrt(pg.dy*pg.dy + pg.dx*pg.dx) / 2;
	pg.dx = 0;
}

void Gravitar::exitPlanet() {

	resetTor();
	pg.X = pianetaAttivo->X;
	pg.Y = pianetaAttivo->Y - pianetaAttivo->Size - 2.6;

	pianetaAttivo = NULL;
}

void Gravitar::EraseBullets(vector<Proiettile> &Proiettili) {
	//cicla su tutti i proiettili e si elimina il proiettile che è fuori dalla schermata di gioco
	if (Proiettili.size() > 0)
	{
		auto i = remove_if(Proiettili.begin(), Proiettili.end(), [&](Proiettile o) {return (o.X < 1 || o.Y < 1 || o.X >= ScreenWidth() - 1 || o.Y >= ScreenHeight() - 1); });
		if (i != Proiettili.end())
			Proiettili.erase(i);
	}
}

void Gravitar::resetTor() {
	//viene resettato il time to shoot delle vecchie torrette 
	for (auto &t : pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Torrette) {
		t.TimeToShoot = (t.pro) ? 300 : 200;
	}
}

#pragma endregion

#pragma region CONTROL

bool Gravitar::Collision(objGame obj1, objGame obj2) {
	float x1 = obj1.X, y1 = obj1.Y, x2 = obj2.X, y2 = obj2.Y;
	/*viene usata la formula di intersezione di due circonferenze per determinare la collisione di due oggetti
	per la torretta viene passato il centro con un raggio di 2 pixel
	per la navicella viene passato il centro con un raggio di 2,5 pixel
	per i proiettili viene passato il centro con un raggio di 0 pixel
	per il terreno viene passata la proiezione del centro dell'altro oggetto sul terreno con raggio un pixel
	per il pianeta viene passato il centro con un raggio variabile tra 3 e 5 pixel a seconda delle dimensioni del pianeta*/
	return sqrtf((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)) < (obj1.Size + obj2.Size);
}

void Gravitar::WrapCoordinate() {
	//sicontrolla la posizione del giocatore e si riposiziona dalla parte opposta della mappa nel caso il giocatore decidesse di uscire da essa
	if (pg.X < 0.0f)	pg.X += (float)ScreenWidth();
	if (pg.X >= (float)ScreenWidth())	pg.X -= (float)ScreenWidth();
	if (pg.Y < 0.0f)	pg.Y += (float)ScreenHeight();
	if (pg.Y >= (float)ScreenHeight()) pg.Y -= (float)ScreenHeight();
}

bool Gravitar::checkDistance(Pianeta p) {
	//si controlla per ogni pianeta che non collida con gli altri. In caso succeda si ritorna true
	for (auto &planet : pianeti) {
		if (abs(p.X - planet.X) < (p.Size + planet.Size) || abs(p.Y - planet.Y) < (p.Size + planet.Size)) {
			return  true;
		}
	}
	return false;
}

Pianeta * Gravitar::PlanetLanding() {
	//si cerca una collisione tra i pianeti e la navicella, in caso si ritorna il puntatore al pianeta 
	for (auto &pian : pianeti) {
		if (Collision(pg, pian))
			return &pian;
	}
	return NULL;
}

void Gravitar::CheckCollisions() {
	//Controlla le varie collisioni che possono avvenire su schermo
	if (pianetaAttivo != NULL) {
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
			auto i = remove_if(pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Torrette.begin(), pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Torrette.end(), [&](Torretta t) {return (Collision(p, t) && p.player); });
			if (i != pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Torrette.end())
			{
				score += (i->pro) ? 500 : 100;
				pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Torrette.erase(i);
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

void Gravitar::changeArea() {
	// si controlla che il giocatore abbia superato il limite massimo della schermata di gioco sulle asscisse
	bool next = pg.X > ScreenWidth();
	//si cambia l'area nel caso il giocatore sia andato oltre la schermata di gioco nelle ascisse (in positivo e negativo)
	if ((pg.X < 0) || next) {

		resetTor();

		//il giocatore viene fatto tornare nella schermata di gioco ma dal lato opposto
		pg.X = next ? pg.X = 5 : pg.X = ScreenWidth() - 5;
		//si aggiona l'area corrente, in positivo se superato il limite massimo, in negativo se superato il limite minimo
		pianetaAttivo->areaCorrente += pianetaAttivo->Aree.size() + (next ? +1 : -1);
		//si evita di eccedere dal numero di aree del pianeta
		pianetaAttivo->areaCorrente = pianetaAttivo->areaCorrente % pianetaAttivo->Aree.size();
		//tutti i proiettili presenti vengono cancellati
		Proiettili.clear();
	}
}

void Gravitar::carbnear() {
	//Controlla se un oggetto carburante è compreso nel raggio di azione del raggio traente 
	auto i = remove_if(pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Carburanti.begin(), pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Carburanti.end(), [&](Carburante c)
	{
		float dx = (c.Y - pg.Y);
		if ((c.Y > pg.Y) && (c.Y < pg.Y + 10) && (c.X < pg.X + dx) && (c.X > pg.X - dx)) {
			//se viene preso un carburante si aumenta il fuel e aggiornano i punti
			pg.fuel += c.liter;
			score += c.pro ? 100 : 50;
			return true;
		}
		else
			return false;
	});

	if (i != pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Carburanti.end())
		//elimina il carburante appena preso
		pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Carburanti.erase(i);
}

#pragma endregion

#pragma region Updates

void Gravitar::updateTorr(float fElapsedTime) {
	//per ogni torretta nell'area si richiama la funzione di update corrispondente 
	for (auto &t : pianetaAttivo->Aree[pianetaAttivo->areaCorrente].Torrette) {
		if (t.pro)
			((TorrettaPro*)&t)->UpdatePro(fElapsedTime, pg.X, pg.Y);
		else
			t.Update(fElapsedTime, pg.X, pg.Y);

		if (t.TorreProiettili.size() > 0)
			//nel caso la torretta avesse generato proiettili essi vengono aggiunti al vector contenente tutti i proiettili del gioco
			Proiettili.insert(Proiettili.begin(), t.TorreProiettili.begin(), t.TorreProiettili.end());
	}
}

void Gravitar::updateBull(float fElapsedTime) {
	// viene richiamato l'update di ogni proiettile 
	for (auto &p : Proiettili)
		p.Update(fElapsedTime);
	//viene richimata la funzione di erase nel caso ci siano proiettili da cancellare
	EraseBullets(Proiettili);
}

void Gravitar::updateNav(float fElapsedTime) {
	//si fa il controllo sui pulsanti premuti dal giocatore e per ognuno di essi si richiama la funzione corrispondente in torretta 
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

void Gravitar::DrawPlanet(Pianeta planet) {
	FillCircle(planet.X, planet.Y, planet.Size, PIXEL_SOLID, planet.Colore);
}

void Gravitar::DrawArea() {
	//quando esiste il pianeta attivo viene presa l'area in cui il giocatore si trova e ne vengono disegnati tutti i punti
	int areaCorrente = pianetaAttivo->areaCorrente;

	for (int i = 0; i < pianetaAttivo->Aree[areaCorrente].Terreno.size() - 1; i++)
		DrawLine(pianetaAttivo->Aree[areaCorrente].Terreno[i].X, pianetaAttivo->Aree[areaCorrente].Terreno[i].Y, pianetaAttivo->Aree[areaCorrente].Terreno[i + 1].X, pianetaAttivo->Aree[areaCorrente].Terreno[i + 1].Y, PIXEL_SOLID, pianetaAttivo->Colore);
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

void Gravitar::DrawBullet(Proiettile bullet) {
	Draw(bullet.X, bullet.Y, PIXEL_SOLID, bullet.Color);
}

void Gravitar::DrawRay() {
	DrawLine(pg.X, pg.Y, pg.X - 5, pg.Y + 10, PIXEL_THREEQUARTERS, FG_CYAN);
	DrawLine(pg.X, pg.Y, pg.X + 5, pg.Y + 10, PIXEL_THREEQUARTERS, FG_CYAN);
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
	if (blink <= 0) {
		blink = 1.0f;
	}

	DrawString(15, 75, L"Move with Arrows");
	DrawString(ScreenWidth() / 2 - 9, ScreenHeight() / 2 + 35, L"Press Space to shoot");
	DrawString(132, 72, L"Press Enter to use the ray");
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

bool Gravitar::OnUserCreate() {
	//Creazione del gioco
	blink = 1.0f;
	pg.Size = 2.5;
	pg.fuel = 10000;
	morto = false;
	gameover = true;
	return true;

}

bool Gravitar::OnUserUpdate(float fElapsedTime) {
	//Ciclo infinito del gioco
	//si pulise la schermata
	Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, 0);
	//Reset Game
	if (m_keys[VK_TAB].bHeld) {
		resetGame();
	}


	if (gameover) {
		if (morto) {
			DrawGameOver(fElapsedTime);
		}
		else {
			DrawTitle(fElapsedTime);
		}
	}
	else
	{
		rayOn = false;
		updateNav(fElapsedTime);

		//UPDATE
		if (pianetaAttivo != NULL) {
			updateBull(fElapsedTime);
			updateTorr(fElapsedTime);
		}


		//EXEC
		if (pianetaAttivo != NULL) {

			//collisioni
			CheckCollisions();
			changeArea();
			if (rayOn)
				carbnear();

			//Controlla i pianeti, quelli morti li rimuove dall'elenco e posiziona il giocatore nel mezzo dell'universo
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

				//Se l'universo è vuoto, crea un nuovo universo
				if (pianeti.size() <= 0)
				{
					newUniverse();
					score += 10000;
				}
			}

			if (pg.Y < 0) {
				Proiettili.clear();
				exitPlanet();
			}

			if (morto) {
				resetTor();
				Proiettili.clear();
				if (vite == 0)
					gameover = true;
				else
					reborn();
			}
			if (pg.fuel <= 0) {
				Proiettili.clear();
				gameover = true;
				morto = true;
			}
		}
		else {
			WrapCoordinate();

			Pianeta *p = PlanetLanding();
			if (p != NULL)
				enterPlanet(p);
		}

		//DRAW
		//richiama le funzioni di disegno relative ad ogni oggetto di gioco
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