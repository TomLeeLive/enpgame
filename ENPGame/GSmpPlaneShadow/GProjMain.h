#pragma once

#if defined(_DEBUG) || defined(DEBUG)
#pragma comment( lib, "GCharCore32d.lib" )	
#else
#pragma comment( lib, "GCharCore32.lib" )
#endif

#if defined(_DEBUG) || defined(DEBUG)
#pragma comment( lib, "GMapCore32d.lib" )
#else
#pragma comment( lib, "GMapCore32.lib" )
#endif

#include "GCoreLibV2.h"
#include "map/GMap.h"
#include "TMatrixEx.h"
#include "GCamera.h"
class GProjMain : public GCoreLibV2
{
public:
	shared_ptr<GCamera>	m_pMainCamera;
	GMap				m_CustomMap;	
	GShape*				m_pBoxShape;
	GShape*				m_pLine;
	D3DXMATRIX			m_matWorld;
	D3DXMATRIX			m_matShadow;
	TMatrixEx			m_mShadowPoint;				
	TMatrixEx			m_mShadowDirection;	
	ComPtr<ID3D11PixelShader>		m_pPixelShader;
	void				RenderShadow(	D3DXMATRIX matWorld, D3DXMATRIX matShadow, 
										D3DXMATRIX* matView, D3DXMATRIX* matProj );
	D3DXMATRIX CreateMatrixShadow( D3DXVECTOR4 plane, D3DXVECTOR4 Light );
public:	
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	//--------------------------------------------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();	

public:
	GProjMain(void);
	virtual ~GProjMain(void);
};
