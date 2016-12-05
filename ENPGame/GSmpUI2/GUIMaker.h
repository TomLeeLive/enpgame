#pragma once
#include "GUIManager.h"

class GUIMaker : public GUIManager
{
public:
	bool		Frame(DXGI_SWAP_CHAIN_DESC*	SwapChainDesc);

public:
	GUIMaker();
	virtual ~GUIMaker();
};

