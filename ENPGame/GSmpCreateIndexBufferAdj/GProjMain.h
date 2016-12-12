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
#include "TSampleObj.h"
#include "GShape.h"
#include "TTerrain.h"
#include "GLightObj.h"
#include "GCamera.h"

class GProjMain : public GCoreLibV2
{
public:
	TTerrain			m_HeightMap;
	TSampleObj			m_SampleObj;
	shared_ptr<GCamera>	m_pMainCamera;
	HRESULT				CreateStateAndBuffer(ID3D11Device* pDevice);	
	//--------------------------------------------------------------------------------------
	// ����Ʈ ���� ���
	//--------------------------------------------------------------------------------------
	D3DXMATRIX			m_mLightWorld;
	D3DXVECTOR3			m_vInitLightPos;
	GLightObj*			m_pSunLight;
	shared_ptr<GPlaneShape>		m_pQuadObj;
public:
	//--------------------------------------------------------------------------------------
	// ������ ���� 
	//--------------------------------------------------------------------------------------
	ComPtr<ID3D11BlendState>			m_pVolumeShadowBS;
	ComPtr<ID3D11DepthStencilState>		m_pVolumeShadowDSS;
	ComPtr<ID3D11VertexShader>			m_pShadowVolumeVS;
	ComPtr<ID3D11GeometryShader>		m_pShadowVolumeGS;
	ComPtr<ID3D11PixelShader>			m_pShadowVolumePS;
	ComPtr<ID3D11BlendState>			m_pQuadBS;
	ComPtr<ID3D11DepthStencilState>		m_pQuadDSS;
public:		
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	bool		DrawDebug(bool bDrawString = true, bool bDrawLine=true);
	//--------------------------------------------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();	
public:
	GProjMain(void);
	virtual ~GProjMain(void);
};
