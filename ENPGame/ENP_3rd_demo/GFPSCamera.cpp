#include "_stdafx.h"
//#include "GProjMain.h"
//#include "GFPSCamera.h"
//
//#include "GInput.h"
//#include "GTimer.h"

int GFPSCamera::WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    if( ( (uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONDBLCLK ) && m_nRotateModelButtonMask & MOUSE_LEFT_BUTTON) ||
        ( (uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONDBLCLK ) && m_nRotateModelButtonMask & MOUSE_MIDDLE_BUTTON) ||
        ( (uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONDBLCLK ) && m_nRotateModelButtonMask & MOUSE_RIGHT_BUTTON) )
    {
        int iMouseX = (short)LOWORD(lParam);
        int iMouseY = (short)HIWORD(lParam);
        m_WorldArcBall.OnBegin( iMouseX, iMouseY );
    }

    if( ( (uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONDBLCLK ) && m_nRotateCameraButtonMask & MOUSE_LEFT_BUTTON) ||
        ( (uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONDBLCLK ) && m_nRotateCameraButtonMask & MOUSE_MIDDLE_BUTTON) ||
        ( (uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONDBLCLK ) && m_nRotateCameraButtonMask & MOUSE_RIGHT_BUTTON) )
    {
        int iMouseX = (short)LOWORD(lParam);
        int iMouseY = (short)HIWORD(lParam);
        m_ViewArcBall.OnBegin( iMouseX, iMouseY );
    }

    if( uMsg == WM_MOUSEMOVE )
    {
        int iMouseX = (short)LOWORD(lParam);
        int iMouseY = (short)HIWORD(lParam);
        m_WorldArcBall.OnMove( iMouseX, iMouseY );
        m_ViewArcBall.OnMove( iMouseX, iMouseY );
    }

    if( (uMsg == WM_LBUTTONUP && m_nRotateModelButtonMask & MOUSE_LEFT_BUTTON) ||
        (uMsg == WM_MBUTTONUP && m_nRotateModelButtonMask & MOUSE_MIDDLE_BUTTON) ||
        (uMsg == WM_RBUTTONUP && m_nRotateModelButtonMask & MOUSE_RIGHT_BUTTON) )
    {
        m_WorldArcBall.OnEnd();
    }

    if( (uMsg == WM_LBUTTONUP && m_nRotateCameraButtonMask & MOUSE_LEFT_BUTTON) ||
        (uMsg == WM_MBUTTONUP && m_nRotateCameraButtonMask & MOUSE_MIDDLE_BUTTON) ||
        (uMsg == WM_RBUTTONUP && m_nRotateCameraButtonMask & MOUSE_RIGHT_BUTTON) )
    {
        m_ViewArcBall.OnEnd();
    }

    if( uMsg == WM_CAPTURECHANGED )
    {
        if( (HWND)lParam != hWnd )
        {
            if( (m_nRotateModelButtonMask & MOUSE_LEFT_BUTTON) ||
                (m_nRotateModelButtonMask & MOUSE_MIDDLE_BUTTON) ||
                (m_nRotateModelButtonMask & MOUSE_RIGHT_BUTTON) )
            {
                m_WorldArcBall.OnEnd();
            }
        
            if( (m_nRotateCameraButtonMask & MOUSE_LEFT_BUTTON) ||
                (m_nRotateCameraButtonMask & MOUSE_MIDDLE_BUTTON) ||
                (m_nRotateCameraButtonMask & MOUSE_RIGHT_BUTTON) )
            {
                m_ViewArcBall.OnEnd();
            }
        }
    }

    
	if( uMsg == WM_MOUSEWHEEL )
	{
           // Update member var state
           m_nMouseWheelDelta += (short)HIWORD(wParam);
	}
    return -1;
}
void GFPSCamera::SetButtonMasks( int nRotateModelButtonMask, int nZoomButtonMask, int nRotateCameraButtonMask ) 
{ 
	m_nRotateModelButtonMask	= nRotateModelButtonMask, 
	m_nZoomButtonMask			= nZoomButtonMask; 
	m_nRotateCameraButtonMask	= nRotateCameraButtonMask; 
}

// 박스의 크기에 따라서 화면에 꽉차게 카메라가 조정된다.
D3DXMATRIX	GFPSCamera::SetObjectView( D3DXVECTOR3 vMax, D3DXVECTOR3 vMin )
{
	D3DXMATRIX	matView;
	D3DXVECTOR3 vCenter = ( vMax + vMin ) * 0.5f;
	float fRadius = D3DXVec3Length( &(vMax-vMin) ) * 0.5f;	

	D3DXVECTOR3 vTarget = D3DXVECTOR3( vCenter.x, vCenter.y, vCenter.z );
	D3DXVECTOR3 vPos = (m_vLookVector *  (fRadius*2) ) * -1.0f;

	D3DXMatrixLookAtLH( &m_matView, &vPos, &vTarget , &D3DXVECTOR3(0.0f, 1.0f, 0.0f) );
	
	m_vCameraPos	= vPos;	
	m_vTargetPos	= vTarget;
	return m_matView;
}
D3DXMATRIX GFPSCamera::SetViewMatrix( D3DXVECTOR3 vPos, D3DXVECTOR3 vTarget, D3DXVECTOR3 vUp )
{
	m_vDefaultEye		= m_vCameraPos	= vPos;	
	m_vDefaultLookAt	= m_vTargetPos	= vTarget;
	D3DXMatrixLookAtLH( &m_matView, &m_vCameraPos, &m_vTargetPos , &vUp );
	
	D3DXQUATERNION qRotation;
	D3DXVECTOR3 vTrans, vScale, vAxis;
	D3DXMATRIX mInvView;
	D3DXQUATERNION q;
	float fAngle;

	if (SUCCEEDED(D3DXMatrixDecompose(&vScale, &qRotation, &vTrans, &m_matView)))
	{
		D3DXQuaternionNormalize(&qRotation, &qRotation);
		D3DXQuaternionToAxisAngle(&qRotation, &vAxis, &fAngle);
		// 반드시 정규화 해야 한다.
		D3DXVec3Normalize(&vAxis, &vAxis);

		q.x = sin(fAngle / 2) * vAxis.x;
		q.y = sin(fAngle / 2) * vAxis.y;
		q.z = sin(fAngle / 2) * vAxis.z;
		q.w = cos(fAngle / 2);
	}
	D3DXMatrixInverse(&mInvView, NULL, &m_matView);
	// The axis basis vectors and camera position are stored inside the 
	// position matrix in the 4 rows of the camera's world matrix.
	// To figure out the yaw/pitch of the camera, we just need the Z basis vector
	D3DXVECTOR3* pZBasis = (D3DXVECTOR3*)&mInvView._31;

	m_fCameraYawAngle = atan2f( pZBasis->x, pZBasis->z );
	float fLen = sqrtf( pZBasis->z * pZBasis->z + pZBasis->x * pZBasis->x );
	m_fCameraPitchAngle = -atan2f( pZBasis->y, fLen );

	return 	UpdateVector();	
}
D3DXMATRIX GFPSCamera::SetProjMatrix( FLOAT fFOV, FLOAT fAspect, FLOAT fNearPlane, FLOAT fFarPlane )
{
    m_fFOV			= fFOV;
    m_fAspect		= fAspect;
    m_fNearPlane	= fNearPlane;
    m_fFarPlane		= fFarPlane;

    D3DXMatrixPerspectiveFovLH( &m_matProj, fFOV, fAspect, fNearPlane, fFarPlane );	
	return m_matProj;
}
D3DXMATRIX GFPSCamera::UpdateVector()
{
	m_vLookVector.x = m_matView._13;
	m_vLookVector.y = m_matView._23;
	m_vLookVector.z = m_matView._33;	
	m_vRightVector.x = m_matView._11;
	m_vRightVector.y = m_matView._21;
	m_vRightVector.z = m_matView._31;	
	m_vUpVector.x = m_matView._12;
	m_vUpVector.y = m_matView._22;
	m_vUpVector.z = m_matView._32;	
	
	D3DXVec3Normalize( &m_vLookVector, &m_vLookVector );
	
	GFrustum::SetMatrix( NULL, &m_matView, &m_matProj );
	GFrustum::CreateFrustum();	

	//g_pMain->UpdateGunPosition();
	return m_matView;
}
D3DXMATRIX GFPSCamera::Update( D3DXVECTOR4 vDirValue )
{
	D3DXMATRIX matRotation;
	D3DXQuaternionRotationYawPitchRoll(			&m_qRotation,	
												vDirValue.y,
												vDirValue.x,
												vDirValue.z );			

	m_vCameraPos += m_vLookVector * vDirValue.w;
	m_fRadius  += vDirValue.w;

	D3DXMatrixAffineTransformation( &matRotation, 1.0f, NULL, &m_qRotation, &m_vCameraPos );
	D3DXMatrixInverse( &m_matView, NULL, &matRotation );

	return UpdateVector();	
}
bool GFPSCamera::Frame()
{
	if (g_pMain->m_pGameSeq[G_SEQ_SINGLE]->m_bGameOver)
		return false;

	//if( g_InputData.bRightHold )
	//{
		m_fCameraYawAngle	+=	D3DXToRadian(g_InputData.iMouseValue[0] *0.1f);
		m_fCameraPitchAngle	+=  D3DXToRadian(g_InputData.iMouseValue[1] *0.1f);
	//}		
	// 카메라 이동 거리 = 속도 + ( 경과시간 * 마우스 휠 변위값 )
	float fValue = g_InputData.iMouseValue[2];
	float fDistance =  m_fSpeed * fValue * g_fSecPerFrame;
	
	if( g_InputData.bSpace )	m_fSpeed += g_fSecPerFrame * 40.0f;
	else						m_fSpeed -= g_fSecPerFrame * 40.0f;
	// 최소값으로 고정
	if( m_fSpeed < 100.0f ) m_fSpeed = 100.0f;

	if( g_InputData.bWKey ) 	MoveLook(g_fSecPerFrame * 5.0f * m_fSpeed);
	if( g_InputData.bSKey )		MoveLook(-g_fSecPerFrame * 5.0f* m_fSpeed);
	if( g_InputData.bDKey )		MoveSide(g_fSecPerFrame * 5.0f* m_fSpeed);
	if( g_InputData.bAKey )		MoveSide(-g_fSecPerFrame * 5.0f* m_fSpeed);
	
	//if( g_InputData.bQKey )		MoveUp(g_fSecPerFrame * 5.0f* m_fSpeed);
	//if( g_InputData.bEKey )		MoveUp(-g_fSecPerFrame * 5.0f* m_fSpeed);

	Update( D3DXVECTOR4( m_fCameraPitchAngle, m_fCameraYawAngle, m_fCameraRollAngle, fDistance) );
	UpdateVector();	
	UpdateCameraDir();
	return true;
}

D3DXMATRIX GFPSCamera::GetRotMatY()
{
	D3DXMATRIX matRotY, matRot180;

	D3DXMatrixIdentity(&matRotY);
	D3DXMatrixIdentity(&matRot180);


	D3DXVECTOR3 vRight, vDir, vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXMatrixRotationY(&matRot180, D3DXToRadian(180.0f));
	D3DXVec3TransformCoord(&vDir, &m_vCameraDir, &matRot180);
	D3DXVec3Normalize(&vDir, &vDir);
	
	D3DXVec3Cross(&vRight, &vUp, &vDir);
	D3DXVec3Cross(&vUp, &vDir, &vRight);



	matRotY._11 = vRight.x;		    matRotY._12 = vRight.y;			matRotY._13 = vRight.z;
	matRotY._21 = vUp.x;			matRotY._22 = vUp.y;			matRotY._23 = vUp.z;
	matRotY._31 = vDir.x;			matRotY._32 = vDir.y;			matRotY._33 = vDir.z;

	return matRotY;
}

void GFPSCamera::UpdateCameraDir() {
	D3DXMATRIX matScl, matRot, matViewInv;

	D3DXVECTOR3 vScl, vTrans;
	D3DXQUATERNION qRot;

	D3DXMatrixIdentity(&matScl);
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matViewInv);



	D3DXMatrixInverse(&matViewInv, NULL, &m_matView);
	D3DXMatrixDecompose(&vScl, &qRot, &vTrans, &matViewInv);

	D3DXMatrixScaling(&matScl, vScl.x, vScl.y, vScl.z);

	vTrans = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXMatrixAffineTransformation(&matRot, 1.0f, NULL, &qRot, &vTrans);

	//m_tbsobj.m_matWorld = matScl * matRot;// *matTrans;

	D3DXMatrixIdentity(&m_matRotY);

	m_matRotY._11 = matRot._11;
	m_matRotY._13 = matRot._13;
	m_matRotY._31 = matRot._31;
	m_matRotY._33 = matRot._33;

	m_vCameraDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	D3DXVec3TransformCoord(&m_vCameraDir, &m_vCameraDir, &m_matRotY);
	D3DXVec3Normalize(&m_vCameraDir, &m_vCameraDir);
}

void GFPSCamera::MoveLook( float fValue )
{
	//g_pMain->m_pSound.Play(SND_BOOTS1, true, true);

	UpdateCameraDir();
	m_vCameraPos += m_vCameraDir * fValue;
}
void GFPSCamera::MoveSide( float fValue )
{
	m_vCameraPos += m_vRightVector * fValue;
}
void GFPSCamera::MoveUp( float fValue )
{
	m_vCameraPos += m_vUpVector * fValue;
}
void GFPSCamera::SetRadius( float fDefaultRadius, float fMinRadius, float fMaxRadius  ) 
{ 
  m_fDefaultRadius = m_fRadius = fDefaultRadius;
  m_fMinRadius = fMinRadius; 
  m_fMaxRadius = fMaxRadius; 
}
void GFPSCamera::SetWindow( int nWidth, int nHeight, float fArcballRadius )
{ 
	m_WorldArcBall.SetWindow( nWidth, nHeight, fArcballRadius ); 
	m_ViewArcBall.SetWindow( nWidth, nHeight, fArcballRadius ); 
}

void GFPSCamera::SetModelCenter( D3DXVECTOR3 vModelCenter ) 
{ 
	m_vModelCenter = vModelCenter;
}
GFPSCamera::GFPSCamera()
{		
	// 추가
	D3DXMatrixIdentity(&m_matRotY);
	m_vCameraDir			= D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	m_vPosDelta				= D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	 
	m_fDefaultRadius		= 0.0f;
    m_fMinRadius			= 1.0f;
    m_fMaxRadius			= FLT_MAX;
	m_fRadius				= 0.0f;

	m_fCameraYawAngle		= 0.0f;
	m_fCameraPitchAngle		= 0.0f;
	m_fCameraRollAngle		= 0.0f;

	m_fSpeed				= 0.0f;

	// 추가
	m_nMouseWheelDelta		= 0;

	m_vModelCenter			= D3DXVECTOR3(0,0,0);

	D3DXMatrixIdentity( &m_matWorld );
    D3DXMatrixIdentity( &m_mModelRot );
    D3DXMatrixIdentity( &m_mModelLastRot );    
    D3DXMatrixIdentity( &m_mCameraRotLast );    

	m_nRotateModelButtonMask  = MOUSE_LEFT_BUTTON;
    m_nZoomButtonMask         = MOUSE_WHEEL;
    m_nRotateCameraButtonMask = MOUSE_RIGHT_BUTTON;


	D3DXMatrixIdentity( &m_matWorld );
	SetProjMatrix( D3DX_PI / 4.0f, 1.0f, 0.1f, 1000.0f );
	SetViewMatrix( D3DXVECTOR3( 0.0f, 0.0f, 10.0f ), D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));
}

GFPSCamera::~GFPSCamera()
{	
}
