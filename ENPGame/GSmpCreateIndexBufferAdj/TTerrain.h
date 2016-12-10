#pragma once
#include "map/GHeightMap.h"
#include "TAdjRep.h"

class TTerrain : public GHeightMap
{
public:
	TAdjacencyRep			m_rep;
	bool m_bAdjacency;
	vector<DWORD>			m_IndexListAdj;
	ComPtr<ID3D11Buffer>	m_pIndexBufferAdj;
public:
	bool CreateIndexData();
	D3DXVECTOR2 GetTextureOfVertex(float fOffsetX, float fOffsetY)
	{
		return D3DXVECTOR2(fOffsetX* 10.0f, fOffsetY* 10.0f);
	};
public:
	TTerrain();
	virtual ~TTerrain();
};

