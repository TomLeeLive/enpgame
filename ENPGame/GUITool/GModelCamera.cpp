#include "stdafx.h"
#include "GModelCamera.h"

D3DXMATRIX GModelCamera::Update( D3DXVECTOR4 vDirValue )
{
	D3DXMATRIX matRotation;
	D3DXMatrixRotationYawPitchRoll( &matRotation, vDirValue.y, vDirValue.x, vDirValue.z );  
    // 기저벡터를 카메라 회전행렬로 변환한다.
    D3DXVECTOR3 vWorldUp,	vWorldLook;
    D3DXVECTOR3 vLocalUp   = D3DXVECTOR3(0,1,0);
    D3DXVECTOR3 vLocalLook = D3DXVECTOR3(0,0,1);
    D3DXVec3TransformCoord( &vWorldUp,		&vLocalUp,		&matRotation );
    D3DXVec3TransformCoord( &vWorldLook,	&vLocalLook,	&matRotation );
    // 카메라 위치를 디렉션벡터* 반지름크기 만큼 이동시킨다.	
    m_vCameraPos = m_vTargetPos - (vWorldLook * vDirValue.w);
	return SetViewMatrix( m_vCameraPos, m_vTargetPos, vWorldUp );
}
void GModelCamera::SetTargetPos( D3DXVECTOR3 vPos )
{
	m_vTargetPos = vPos;
};
GModelCamera::GModelCamera()
{	
}

GModelCamera::~GModelCamera()
{	
}
