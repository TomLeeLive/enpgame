#pragma once
#include "GObject.h"

class TSampleObj : public GObject
{
public:
	bool		PreDraw(ID3D11DeviceContext*    pContext, TObjWM* pUnit, bool bCommand);
	bool		PostDraw(ID3D11DeviceContext*    pContext, TObjWM* pUnit, bool bCommand);
public:
	TSampleObj();
	virtual ~TSampleObj();
};

