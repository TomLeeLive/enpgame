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

#include "GZombie.h"

const int MAX_OBJECT_CNT = 3;
//struct SHADOW_CONSTANT_BUFFER
//{
//	D3DXMATRIX			g_matShadow;
//	float				g_ShadowID;
//	float				g_iNumKernel;
//	float				fZ, fW;
//};

class GProjMain : public GCoreLibV2
{
public:	
	vector<shared_ptr<GZombie>>	m_HeroObj;


	shared_ptr<GCamera>	m_pMainCamera;
	GMap				m_CustomMap;	
	GBoxShape*			m_pBoxShape;
	D3DXVECTOR3			m_vLightPos;
	float				m_fObjID[MAX_OBJECT_CNT];
	D3DXMATRIX			m_matWorld[MAX_OBJECT_CNT];
	D3DXMATRIX			m_matShadow;
	D3DXMATRIX			m_matTexture;
	D3DXMATRIX			m_matShadowView;
	D3DXMATRIX			m_matShadowProj;
	bool				m_bColorTexRender;
	//--------------------------------------------------------------------------------------
	// 랜더타켓 및 깊이/스텐실 버퍼
	//--------------------------------------------------------------------------------------	
	GDxRT							m_RT;
	GPlaneShape*					m_pQuad;
	SHADOW_CONSTANT_BUFFER			m_cbShadow;
	ComPtr<ID3D11Buffer>			m_pShadowConstantBuffer;
	ComPtr<ID3D11VertexShader>		m_pShadowVS;
	ComPtr<ID3D11PixelShader>		m_pShadowPS;

	//ComPtr<ID3D11VertexShader>		m_pCharShadowVS;
	//ComPtr<ID3D11PixelShader>		m_pCharShadowPS;
public:	
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	void		RenderShadow( D3DXMATRIX* matShadow,D3DXMATRIX* matView, D3DXMATRIX* matProj );
	void		RenderObject( D3DXMATRIX* matView, D3DXMATRIX* matProj );
	//--------------------------------------------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();	
public:
	GProjMain(void);
	~GProjMain(void);
};
