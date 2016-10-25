
// Practice.h : Practice 응용 프로그램에 대한 주 헤더 파일
//
#pragma once
const UINT g_iTextureRTSize = 1024;
#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.
#include "GBasisLib_0.h"
#include "GModelViewCamera.h"
#include "GUtils.h"

#include <memory>
#include "GSprite.h"

// CPracticeApp:
// 이 클래스의 구현에 대해서는 Practice.cpp을 참조하십시오.
//

class CPracticeApp : public CWinApp, public GBasisLib_0 
{
public:
	CPracticeApp();
	//shared_ptr<GModelViewCamera > m_pMainCamera;
	shared_ptr<GCamera > m_pMainCamera;
public:
	GPlaneShape				m_BigPlane;
	GSprite*				m_pSprite;
	ComPtr<ID3D11PixelShader>			m_pPS;
	D3DXVECTOR4				m_vMaterial;
	D3DXMATRIX				m_matPlaneWorld;
	D3DXMATRIX				m_mPlanWorld;
	D3DXMATRIX				m_matWorld;
	shared_ptr<GPlaneShape> m_pPlane;
	shared_ptr<GPlaneShape> m_pScreen;
public:
	bool					check;

	ID3D11BlendState*           m_pAlphaBlendFactor;
	ID3D11BlendState*			m_pAlphaBlend;

	//--------------------------------------------------------------------------------------
	// 랜더타켓 및 깊이/스텐실 버퍼
	//--------------------------------------------------------------------------------------	
	//GDxRT		m_RT;

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	void ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext);
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	bool RenderPlane();
	HRESULT	SetBlendState();
	//bool		RenderScene(int iViewPort, GSprite* pPlane);
	//--------------------------------------------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
// 구현입니다.
	afx_msg void OnAppAbout();
	virtual BOOL OnIdle(LONG iCount);
	DECLARE_MESSAGE_MAP()
};

extern CPracticeApp theApp;
