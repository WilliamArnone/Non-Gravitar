#pragma once
#include "Torretta.h"
class TorrettaPro : public Torretta
{
public:
	TorrettaPro();
	TorrettaPro(float xu, float yu, float xl, float yl, float xr, float yr);
	void UpdatePro(float fElapsedTime, float Px, float Py);
	~TorrettaPro();
};

