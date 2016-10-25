
// KEffectTool.h : KEffectTool 응용 프로그램에 대한 주 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.
#include "GBasisLib_0.h"
#include "GModelViewCamera.h"
#include "GUtils.h"

#include <memory>
#include "GSprite.h"

// CKEffectToolApp:
// 이 클래스의 구현에 대해서는 KEffectTool.cpp을 참조하십시오.
//

class CKEffectToolApp : public CWinApp,public GBasisLib_0
{
public:
	CKEffectToolApp();
	shared_ptr<GCamera > m_pMainCamera;
public:
	GPlaneShape				m_BigPlane;
	GSprite*				m_pSprite;
	ComPtr<ID3D11PixelShader>	m_pPS;
	D3DXVECTOR4				m_vMaterial;
	D3DXMATRIX				m_matPlaneWorld;
	D3DXMATRIX				m_mPlanWorld;
	D3DXMATRIX				m_matWorld;
	shared_ptr<GPlaneShape> m_pPlane;
	shared_ptr<GPlaneShape> m_pScreen;
public:
	bool check; // play button check
	ID3D11BlendState*           m_pAlphaBlendFactor;
	ID3D11BlendState*			m_pAlphaBlend;
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
	HRESULT		CreateResource();
	HRESULT		DeleteResource();

// 구현입니다.
	afx_msg void OnAppAbout();
	virtual BOOL OnIdle(LONG iCount);
	DECLARE_MESSAGE_MAP()
};

extern CKEffectToolApp theApp;
