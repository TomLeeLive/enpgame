#pragma once
#include "map/GMap.h"
class GHeight : public GMap
{
public:
	vector<float> m_fHeightList;
public:
	bool CreateHeightMap(TCHAR* strHeightMap);
	float GetHeightOfVertex(UINT Index);
	D3DXVECTOR4 GetColorOfVertex(UINT Index);
	float GetHeightmap(int row, int col);
public:
	GHeight();
	virtual ~GHeight();
};

