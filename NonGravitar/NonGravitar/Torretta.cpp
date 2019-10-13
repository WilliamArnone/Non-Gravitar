#include "Torretta.h"

Torretta::Torretta()
{
}

void Torretta::Update(float fElapsedTime) {
}

/*Proiettile Torretta::Shoot(){
	//Primo tipo di Torretta Spara
	if (type == 1 && TimeToShoot == 0)
	{
		vecBullets.push_back({ 0, x3,y3, 50.0f * sinf(angle), -50.0f * cosf(angle), 100.0f,false });
		TimeToShoot = 500;
	}
	//Secondo tipo di torretta
	else if (Base.P[pianetaCorrente].A[AreaCorrente].T.type == 2 && Base.P[pianetaCorrente].A[AreaCorrente].T.TimeToShoot == 0)
	{
		vecBullets.push_back({ 0, Base.P[pianetaCorrente].A[AreaCorrente].T.x3,Base.P[pianetaCorrente].A[AreaCorrente].T.y3, 30.0f * sinf(Base.P[pianetaCorrente].A[AreaCorrente].T.angle + 0.3), -30.0f * cosf(Base.P[pianetaCorrente].A[AreaCorrente].T.angle + 0.3), 100.0f,false });
		vecBullets.push_back({ 0, Base.P[pianetaCorrente].A[AreaCorrente].T.x3,Base.P[pianetaCorrente].A[AreaCorrente].T.y3, 30.0f * sinf(Base.P[pianetaCorrente].A[AreaCorrente].T.angle), -30.0f * cosf(Base.P[pianetaCorrente].A[AreaCorrente].T.angle), 100.0f,false });
		vecBullets.push_back({ 0, Base.P[pianetaCorrente].A[AreaCorrente].T.x3,Base.P[pianetaCorrente].A[AreaCorrente].T.y3, 30.0f * sinf(Base.P[pianetaCorrente].A[AreaCorrente].T.angle - 0.3), -30.0f * cosf(Base.P[pianetaCorrente].A[AreaCorrente].T.angle - 0.3), 100.0f,false });
		Base.P[pianetaCorrente].A[AreaCorrente].T.TimeToShoot = 640;
	}
}*/

Torretta::~Torretta()
{
}