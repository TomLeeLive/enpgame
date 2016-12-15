#pragma once

#define UVNum 20
#include "map/GHeightMap.h"
class GTileMap : public GHeightMap
{
public:
	bool CreateVertexData();
public:
	GTileMap();
	virtual ~GTileMap();
};

