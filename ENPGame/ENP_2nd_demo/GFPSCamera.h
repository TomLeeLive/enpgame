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
	// Ÿ�� ��ġ�� ���� �Ÿ�(������)�� �����Ѵ�.
	//--------------------------------------------------------------------------------------
	virtual void				SetRadius( float fDefaultRadius=5.0f, float fMinRadius=1.0f, float fMaxRadius=FLT_MAX  );
public:			
	//--------------------------------------------------------------------------------------
	// �߰� : �� ���⺤�� ���� 
	//--------------------------------------------------------------------------------------
	virtual D3DXMATRIX			UpdateVector();
	//--------------------------------------------------------------------------------------
	// ������Ʈ�� ȭ�鿡 ���߾� �� ��� ���� 
	//--------------------------------------------------------------------------------------
	virtual D3DXMATRIX			SetObjectView(	D3DXVECTOR3 vMax, 
												D3DXVECTOR3 vMin );	
	//--------------------------------------------------------------------------------------
	// �� ��� ���  
	//--------------------------------------------------------------------------------------
	virtual D3DXMATRIX			SetViewMatrix(	D3DXVECTOR3 vPos, 
												D3DXVECTOR3 vTarget= D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), 
												D3DXVECTOR3 vUp = D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
	//--------------------------------------------------------------------------------------
	// ���� ��� ��� 
	//--------------------------------------------------------------------------------------
	virtual D3DXMATRIX			SetProjMatrix(	FLOAT fFOV, 
												FLOAT fAspect, 
												FLOAT fNearPlane, 
												FLOAT fFarPlane );
	//--------------------------------------------------------------------------------------
	// ī�޶� ��ġ ���� 
	//--------------------------------------------------------------------------------------
	virtual void				MoveLook( float fValue );
	virtual void				MoveSide( float fValue );	
	virtual void				MoveUp( float fValue );	
	//--------------------------------------------------------------------------------------
	// ���Ϸ� ���� ���� �� ��� ��� 
	//--------------------------------------------------------------------------------------
	virtual D3DXMATRIX			Update( D3DXVECTOR4 vDirValue );
	virtual bool				Frame();

	// ȸ�� �� �̵��� ������ ��ư ���� 
	virtual void				SetButtonMasks( int nRotateModelButtonMask, int nZoomButtonMask, int nRotateCameraButtonMask );
	//--------------------------------------------------------------------------------------
	// ������ ����� ������ �ݿ��Ѵ�. 
	//--------------------------------------------------------------------------------------
	virtual void				SetWindow( int nWidth, int nHeight, float fArcballRadius=0.9f );		
	//--------------------------------------------------------------------------------------
	// ������ �޼����� ����Ͽ� ī�޶� ���� 
	//--------------------------------------------------------------------------------------
	virtual int					WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	//--------------------------------------------------------------------------------------
	// �� ȸ�� �߽���ġ�� �����Ѵ�.
	//--------------------------------------------------------------------------------------
	virtual void				SetModelCenter( D3DXVECTOR3 vModelCenter );

	virtual void				SetTargetPos( D3DXVECTOR3 vPos ) { m_vTargetPos = vPos; };

public:
	//--------------------------------------------------------------------------------------
	// ����Լ�
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

