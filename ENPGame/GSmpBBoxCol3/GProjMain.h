#pragma once

#include "GShape.h"
#include "GBackViewCamera.h"
#include "GBBox.h"

//--------------------------------------------------------------------------------------
// CameraViewStyle
//--------------------------------------------------------------------------------------
T_STR CameraViewStyle[] =
{
	_T("Top g_matView"),
	_T("Front g_matView"),
	_T("Side g_matView"),
	_T("User g_matView"),
};

#define G_MACRO_ENEMYBOX 1


class GProjMain : public GCoreLibV2
{
public:
	GSelect							m_Select;
	G_RAY							m_Ray;
	bool ChkOBBToRay(GBBox* pBox, G_RAY* pRay);
	D3DXVECTOR3					m_vLook;


	GBBox						m_pBBox;
	GBoxShape					m_pBox;

#ifdef G_MACRO_ENEMYBOX
	D3DXMATRIX					m_matWorldEnemy;
	GBBox						m_pBBoxEnemy;
	GBoxShape					m_pBoxEnemy;
#endif

	GPlaneShape					m_pPlane;
	GDirectionLineShape			m_pDirectionLine;
	GCamera*					m_pMainCamera;
	//--------------------------------------------------------------------------------------
	// Matrix
	//--------------------------------------------------------------------------------------
	D3DXMATRIX					m_matScale;
	D3DXMATRIX					m_matRotation;
	D3DXMATRIX					m_matTrans;

	D3DXMATRIX					m_matWorld;
	D3DXMATRIX					m_World[2];
	D3DXMATRIX					m_matWorldPlaneBase;

	//--------------------------------------------------------------------------------------
	// 카메라 
	//--------------------------------------------------------------------------------------	
	UINT						m_iCameraType;
	//--------------------------------------------------------------------------------------
	// 카메라 회전 정보
	//--------------------------------------------------------------------------------------
	float						m_fCameraYaw;
	float						m_fCameraPitch;
	float						m_fCameraRoll;
	float						m_fRadius;

public:	
	bool		Init();
	bool		Frame();
	bool		Render();	
	bool		Release();
	bool		DrawDebug();
	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//----------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();

public:
	GProjMain(void);
	virtual ~GProjMain(void);
};

extern GProjMain*	g_pMain; //외부 연결 범위 선언