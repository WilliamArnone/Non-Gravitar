#pragma once
#include "Torretta.h"
class TorrettaPro : public Torretta
{
public:
	TorrettaPro();
	TorrettaPro(float x, float y, float Angle);
	void UpdatePro(float fElapsedTime, float Px, float Py);
	~TorrettaPro();
};

