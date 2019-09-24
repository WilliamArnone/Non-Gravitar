#include "Navicella.h"

Navicella::Navicella()
{
}

Navicella::~Navicella()
{
}

void Navicella::setShip() {
	player.x1 = ScreenWidth() / 2.0f;
	player.y1 = ScreenHeight() / 2.0f;
	player.x2 = 0;
	player.y2 = 0;
	player.angle = 0;
	player.life = 3;
	player.fuel = 10000;
}

void Navicella::ShipMove(float fElapsedTime) {
	// Steer Ship
	if (m_keys['A'].bHeld)
		player.angle -= 5.0f * fElapsedTime;
	if (m_keys['D'].bHeld)
		player.angle += 5.0f * fElapsedTime;

	//Controllo se il turbo del secondo tipo di carburante è entrato in azione
	if (Base.P[pianetaCorrente].speed)
	{
		Base.P[pianetaCorrente].timer--;
		// Thrust? Apply ACCELERATION
		if (m_keys['W'].bHeld)
		{
			// ACCELERATION changes VELOCITY (with respect to time)
			if (player.x2 < 50 && player.y2 > -50) {
				player.x2 += sin(player.angle) * 40.0f * fElapsedTime;
				player.y2 += -cos(player.angle) * 40.0f * fElapsedTime;
			}
		}
		if (Base.P[pianetaCorrente].timer <= 0)
			Base.P[pianetaCorrente].speed = false;
	}
	else {
		// Thrust? Apply ACCELERATION
		if (m_keys['W'].bHeld)
		{
			if (player.fuel >= 0) {
				player.fuel--;
				// ACCELERATION changes VELOCITY (with respect to time)
				if (player.x2 < 50 && player.y2 > -50) {
					player.x2 += sin(player.angle) * 15.0f * fElapsedTime;
					player.y2 += -cos(player.angle) * 15.0f * fElapsedTime;
				}
			}
		}
	}

	if (m_keys['W'].bReleased || !m_keys['W'].bHeld) {
		// Deceleration reset VELOCITY
		player.x2 = 0;
		player.y2 = 0;
	}

	if (m_keys['E'].bReleased && position == 1)
	{
		//Shooting Player's Bullet
		vecBullets.push_back({ 0, player.x1, player.y1 , 50.0f * sinf(player.angle), -50.0f * cosf(player.angle), 100.0f, true });
	}

	// VELOCITY changes POSITION (with respect to time)
	player.x1 += player.x2 * fElapsedTime;
	player.y1 += player.y2 * fElapsedTime;
	if (player.x1 > ScreenWidth() && position == 1) {
		vecBullets.clear();
		if (AreaCorrente < 9) {
			AreaCorrente++;
		}
		else {
			AreaCorrente = 0;
		}
	}
	if (player.x1 < 0 && position == 1) {
		vecBullets.clear();
		if (AreaCorrente > 0) {
			AreaCorrente--;
		}
		else {
			AreaCorrente = 9;
		}
	}

}