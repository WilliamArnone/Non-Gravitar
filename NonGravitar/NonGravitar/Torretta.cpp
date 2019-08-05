#include "Torretta.h"



Torretta::Torretta()
{
}

Proiettile Torretta::Shoot()
{

	//scrivi qui
	return Proiettile();
}

void Torretta::Update(float fElapsedTime) {

	TimeToShoot -= fElapsedTime;

}

Torretta::~Torretta()
{
}
