#pragma once
class collision
{
public:
	collision();
	bool Collision(float x1, float y1, float x2, float y2, float xp, float yp, float ScreenHeight); //Collision	
	bool Collision(float x1, float y1, float x2, float y2); //Collision
	~collision();
};

