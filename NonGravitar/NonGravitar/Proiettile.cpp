#include "Proiettile.h"



#include "Proiettile.h"

Proiettile::Proiettile()
{
}

Proiettile::~Proiettile()
{
}

void Proiettile::Update(float fElapsedTime) {
	x += dx * fElapsedTime;
	y += dy * fElapsedTime;
	angle -= 1.0f * fElapsedTime;
}

bool Proiettile::IsOutOfMap(float width, float heigth) {
	if (x < 1 || y < 1 || x >= width - 1 || y >= heigth - 1)
		return true;
}

/* //Collision with Player
if (Collision(b.x, b.y, player.x1, player.y1) && !b.player)
{
	player.life--;
	b.x = -1000;
}
//Collision with Turret
if (Collision(b.x, b.y, Base.P[pianetaCorrente].A[AreaCorrente].T.x3, Base.P[pianetaCorrente].A[AreaCorrente].T.y3) && b.player)
	Base.P[pianetaCorrente].A[AreaCorrente].T.dead = true;
----------------------------------------
for (auto &b : vecBullets)
{
	if (b.x < Base.P[pianetaCorrente].A[AreaCorrente].x[0]) {
		auto i = remove_if(vecBullets.begin(), vecBullets.end(), [&](sSpaceObject o) { return Collision(0, ScreenHeight(), Base.P[pianetaCorrente].A[AreaCorrente].x[0], Base.P[pianetaCorrente].A[AreaCorrente].y[0], b.x, b.y); });
		if (i != vecBullets.end())
			vecBullets.erase(i);
	}
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
	}
}
}*/