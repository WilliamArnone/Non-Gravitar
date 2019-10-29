#include "Torretta.hpp"

Torretta::Torretta() {}

Torretta::~Torretta() {}

Torretta::Torretta(float x, float y, float Angle) :objGame(x, y, 2)
{
	angle = Angle;

	TimeToShoot = 300;
	pro = false;
	Color = 3;
}

void Torretta::Update(float fElapsedTime, float Px, float Py) {
	//Viene modificato l'angolo di puntamento tra la torretta ed il giocatore e inoltre viene azzerato il vettore proiettili relativo a questa torretta
	float anglep = atan2f(Px - X, Y - Py);
	TorreProiettili.clear();

	/*Viene fatto un conto alla rovescia, se il valore è pari o minore di 0 vengono inseriti all'interno del 
	vettore proiettili, i proiettili appena sparati dalla torretta, e resetta il timer al suo valore originale
	altrimenta decrementa il timer ed esce dalla funzione*/
	if (TimeToShoot <= 0) {
		TorreProiettili.push_back({ false, X + sinf(angle)*4.0f, Y - cosf(angle)*4.0f, anglep - 0.08f });
		TorreProiettili.push_back({ false, X + sinf(angle)*4.0f, Y - cosf(angle)*4.0f, anglep + 0.08f });
		TimeToShoot = 300;
	}
	else
		TimeToShoot = TimeToShoot - 1 * fElapsedTime;
}