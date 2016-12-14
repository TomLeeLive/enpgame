#pragma once
#include "map/GHeightMap.h"
class GTileMap : public GHeightMap
{
public:
	bool CreateVertexData();
public:
	GTileMap();
	virtual ~GTileMap();
};

