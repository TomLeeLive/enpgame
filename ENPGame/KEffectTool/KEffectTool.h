
// KEffectTool.h : KEffectTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.
#include "GBasisLib_0.h"
#include "GModelViewCamera.h"
#include "GUtils.h"

#include <memory>
#include "GSprite.h"

// CKEffectToolApp:
// �� Ŭ������ ������ ���ؼ��� KEffectTool.cpp�� �����Ͻʽÿ�.
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

// �����Դϴ�.
	afx_msg void OnAppAbout();
	virtual BOOL OnIdle(LONG iCount);
	DECLARE_MESSAGE_MAP()
};

extern CKEffectToolApp theApp;
