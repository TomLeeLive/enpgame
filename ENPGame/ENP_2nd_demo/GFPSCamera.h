#pragma once
//#include "GArcBall.h"
//#include "GFrustum.h"

#define MOUSE_LEFT_BUTTON   0x01
#define MOUSE_MIDDLE_BUTTON 0x02
#define MOUSE_RIGHT_BUTTON  0x04
#define MOUSE_WHEEL         0x08

class GFPSCamera : public GCamera
{
public :
	D3DXVECTOR3					m_vCameraDir;
	D3DXMATRIX					m_matRotY;
	D3DXMATRIX					GetRotMatY();
	//--------------------------------------------------------------------------------------
	// 타켓 위치로 부터 거리(반지름)을 지정한다.
	//--------------------------------------------------------------------------------------
	virtual void				SetRadius( float fDefaultRadius=5.0f, float fMinRadius=1.0f, float fMaxRadius=FLT_MAX  );
public:			
	//--------------------------------------------------------------------------------------
	// 추가 : 뷰 방향벡터 저장 
	//--------------------------------------------------------------------------------------
	virtual D3DXMATRIX			UpdateVector();
	//--------------------------------------------------------------------------------------
	// 오브젝트를 화면에 맞추어 뷰 행렬 제어 
	//--------------------------------------------------------------------------------------
	virtual D3DXMATRIX			SetObjectView(	D3DXVECTOR3 vMax, 
												D3DXVECTOR3 vMin );	
	//--------------------------------------------------------------------------------------
	// 뷰 행렬 계산  
	//--------------------------------------------------------------------------------------
	virtual D3DXMATRIX			SetViewMatrix(	D3DXVECTOR3 vPos, 
												D3DXVECTOR3 vTarget= D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), 
												D3DXVECTOR3 vUp = D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
	//--------------------------------------------------------------------------------------
	// 투영 행렬 계산 
	//--------------------------------------------------------------------------------------
	virtual D3DXMATRIX			SetProjMatrix(	FLOAT fFOV, 
												FLOAT fAspect, 
												FLOAT fNearPlane, 
												FLOAT fFarPlane );
	//--------------------------------------------------------------------------------------
	// 카메라 위치 정보 
	//--------------------------------------------------------------------------------------
	virtual void				MoveLook( float fValue );
	virtual void				MoveSide( float fValue );	
	virtual void				MoveUp( float fValue );	
	//--------------------------------------------------------------------------------------
	// 오일러 각에 따른 뷰 행렬 계산 
	//--------------------------------------------------------------------------------------
	virtual D3DXMATRIX			Update( D3DXVECTOR4 vDirValue );
	virtual bool				Frame();

	// 회전 및 이동에 적용할 버튼 세팅 
	virtual void				SetButtonMasks( int nRotateModelButtonMask, int nZoomButtonMask, int nRotateCameraButtonMask );
	//--------------------------------------------------------------------------------------
	// 윈도우 사이즈가 변경을 반영한다. 
	//--------------------------------------------------------------------------------------
	virtual void				SetWindow( int nWidth, int nHeight, float fArcballRadius=0.9f );		
	//--------------------------------------------------------------------------------------
	// 윈도우 메세지를 사용하여 카메라 제어 
	//--------------------------------------------------------------------------------------
	virtual int					WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	//--------------------------------------------------------------------------------------
	// 모델 회전 중심위치를 지정한다.
	//--------------------------------------------------------------------------------------
	virtual void				SetModelCenter( D3DXVECTOR3 vModelCenter );

	virtual void				SetTargetPos( D3DXVECTOR3 vPos ) { m_vTargetPos = vPos; };

public:
	//--------------------------------------------------------------------------------------
	// 멤버함수
	//--------------------------------------------------------------------------------------
	virtual D3DXMATRIX*		GetWorldMatrix() 	{ return &m_matWorld; };
	virtual D3DXMATRIX*		GetViewMatrix() 	{ return &m_matView; }
	virtual D3DXMATRIX*		GetProjMatrix() 	{ return &m_matProj; }
	
	virtual D3DXVECTOR3*	GetEyePt() 			{ return &m_vCameraPos; }
	virtual D3DXVECTOR3*	GetLookAtPt() 		{ return &m_vTargetPos; }
	virtual float			GetNearClip() 		{ return m_fNearPlane; }
	virtual float			GetFarClip() 		{ return m_fFarPlane; }
	
	virtual float			GetYawAngle() 		{ return m_fCameraYawAngle; }
	virtual float			GetPitchAngle() 	{ return m_fCameraPitchAngle; }
	virtual float			GetRollAngle() 		{ return m_fCameraRollAngle; }
	
	virtual D3DXVECTOR3*	GetRightVector() 	{ return &m_vRightVector; }
	virtual D3DXVECTOR3*	GetLookVector() 	{ return &m_vLookVector; }
	virtual D3DXVECTOR3*	GetUpVector() 		{ return &m_vUpVector; }

	virtual float			GetRadius() 		{ return m_fRadius; }
public:
	GFPSCamera(void);
	virtual ~GFPSCamera(void);
};

