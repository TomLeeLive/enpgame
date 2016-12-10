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

struct SHADOW_CONSTANT_BUFFER
{
	D3DXMATRIX			g_matShadow[2];	
};
class GProjMain : public GCoreLibV2
{
public:
	shared_ptr<GCamera>	m_pMainCamera;
	GMap				m_CustomMap;	
	GShape*				m_pBoxShape;
	GShape*				m_pLine;
	D3DXMATRIX			m_matWorld[2];
	D3DXMATRIX			m_matShadow[2];
	D3DXMATRIX			m_matTexture;
	ComPtr<ID3D11PixelShader>		m_pPixelShader;

	SHADOW_CONSTANT_BUFFER  m_cbShadow;
	ComPtr<ID3D11Buffer>			m_pConstantBuffer;
	//--------------------------------------------------------------------------------------
	// 랜더타켓 및 깊이/스텐실 버퍼
	//--------------------------------------------------------------------------------------	
	//TMiniMap			m_MiniMap;
	GDxRT		m_RT[2];
	GPlaneShape*		m_pQuad;
	
public:	
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	void		RenderShadow( D3DXMATRIX* matWorld, D3DXMATRIX* matShadow, 
							  D3DXMATRIX* matView, D3DXMATRIX* matProj );
	void		RenderObject( D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj );
	//--------------------------------------------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();	
public:
	GProjMain(void);
	virtual ~GProjMain(void);
};
