#pragma once
#include "GCamera.h"

class GModelCamera : public GCamera
{
public:	
	//--------------------------------------------------------------------------------------
	// ���Ϸ� ���� ���� �� ��� ��� 
	//--------------------------------------------------------------------------------------
	D3DXMATRIX			Update( D3DXVECTOR4 vDirValue = D3DXVECTOR4( 0,0,0,0));
public:
	void				SetTargetPos( D3DXVECTOR3 vPos );
public:
	GModelCamera(void);
	~GModelCamera(void);
};
