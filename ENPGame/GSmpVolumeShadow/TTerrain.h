#pragma once
#include "map/GHeightMap.h"
class TTerrain : public GHeightMap
{
public:
	D3DXVECTOR2 GetTextureOfVertex(float fOffsetX, float fOffsetY)
	{
		return D3DXVECTOR2(fOffsetX* 10.0f, fOffsetY* 10.0f);
	};
public:
	TTerrain();
	virtual ~TTerrain();
};

