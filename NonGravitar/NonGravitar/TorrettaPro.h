#pragma once
#include "Torretta.h"
class TorrettaPro : public Torretta
{
public:
	TorrettaPro();
	TorrettaPro(float xu, float yu, float xl, float yl, float xr, float yr);
	void Update(float fElapsedTime, float Px, float Py);
	~TorrettaPro();
};

