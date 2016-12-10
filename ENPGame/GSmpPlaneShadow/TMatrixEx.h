#pragma once
#include "GMatrix.h"

//D3DXMATRIX* WINAPI TD3DXMatrixShadow(D3DXMATRIX *pout, 
//	 CONST D3DXVECTOR4 *plight, 
//	 CONST D3DXPLANE *pplane)
// {
//     D3DXPLANE Nplane;
//     FLOAT dot;
// 
//     D3DXPlaneNormalize(&Nplane, pplane);
//     dot = D3DXPlaneDot(&Nplane, plight);
//     pout->m[0][0] = dot - Nplane.a * plight->x;
//     pout->m[0][1] = -Nplane.a * plight->y;
//     pout->m[0][2] = -Nplane.a * plight->z;
//     pout->m[0][3] = -Nplane.a * plight->w;
//     pout->m[1][0] = -Nplane.b * plight->x;
//     pout->m[1][1] = dot - Nplane.b * plight->y;
//     pout->m[1][2] = -Nplane.b * plight->z;
//     pout->m[1][3] = -Nplane.b * plight->w;
//     pout->m[2][0] = -Nplane.c * plight->x;
//     pout->m[2][1] = -Nplane.c * plight->y;
//     pout->m[2][2] = dot - Nplane.c * plight->z;
//     pout->m[2][3] = -Nplane.c * plight->w;
//     pout->m[3][0] = -Nplane.d * plight->x;
//     pout->m[3][1] = -Nplane.d * plight->y;
//     pout->m[3][2] = -Nplane.d * plight->z;
//     pout->m[3][3] = dot - Nplane.d * plight->w;
//     return pout;
// }

class TMatrixEx : public GMatrix
{	
public:
	GMatrix CreateMatrixShadow( Vector4* plane, Vector4* Light );
	GMatrix CreateMatrixShadowD( Vector4* plane, Vector4* Light );
public:
	TMatrixEx();
	virtual ~TMatrixEx();
};