#pragma once
#include "GMatrix.h"

GMatrix WINAPI TMatrixShadow( Vector4 *pPlane, Vector4 *pLight );

class TMatrixEx : public GMatrix
{	
public:
	GMatrix CreateMatrixShadow( Vector4* plane, Vector4* Light );
	GMatrix CreateMatrixShadowD( Vector4* plane, Vector4* Light );
public:
	TMatrixEx();
	~TMatrixEx();
};