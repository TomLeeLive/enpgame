#pragma once

#if defined(_DEBUG) || defined(DEBUG)
#pragma comment( lib, "GMapCore32d.lib" )
#else
#pragma comment( lib, "GMapCore32.lib" )
#endif


#include "GCoreLibV2.h"
#include "GShape.h"
#include "map/GHeightMap.h"
#include "GCamera.h"
#include "GBoxObj.h"
#include "GLightObj.h"

const int g_iNumLight = 3;

struct LIGHT_CONSTANT_BUFFER1
{
	// Material
	D3DXVECTOR4			g_cAmbientMaterial[g_iNumLight];
	D3DXVECTOR4			g_cDiffuseMaterial[g_iNumLight];
	D3DXVECTOR4			g_cSpecularMaterial[g_iNumLight];
	D3DXVECTOR4			g_cEmissionMaterial[g_iNumLight];
	// Light
	D3DXVECTOR4			g_cAmbientLightColor[g_iNumLight];
	D3DXVECTOR4			g_cDiffuseLightColor[g_iNumLight];
	D3DXVECTOR4			g_cSpecularLightColor[g_iNumLight];
};
struct LIGHT_CONSTANT_BUFFER2
{
	D3DXMATRIX			g_matInvWorld[g_iNumLight];
	D3DXVECTOR4			g_vLightDir[g_iNumLight]; // w = light damping(attenuation) : ����
	D3DXVECTOR4			g_vLightPos[g_iNumLight]; // w = light radius
	D3DXVECTOR4			g_vEyeDir[g_iNumLight];// w = light intensity : ����
	D3DXVECTOR4			g_vEyePos[g_iNumLight];// w = light radius		
};
struct LIGHT_CONSTANT_BUFFER3
{
	D3DXVECTOR4			g_vSpotInfo[g_iNumLight];
	//float				g_fFalloff;		// ���� �ܰ� �ܺ� ���� �ֵ�( Luminance )
	//float				g_fTheta;		// ���� ���� ���� ����		
	//float				g_fPhi;			// �ܺ� ���� ���� ����
};

const int g_iMaxLight = 3;

class GProjMain : public GCoreLibV2
{
public:
	GHeightMap		m_HeightMap;
	GLineShape		m_LineDraw;
	shared_ptr<GCamera > m_pMainCamera;
	GBoxObj			m_SphereObj;
	D3DXVECTOR3		m_vLightVector;
	LIGHT_CONSTANT_BUFFER1   m_cbLight1;
	LIGHT_CONSTANT_BUFFER2   m_cbLight2;
	LIGHT_CONSTANT_BUFFER3   m_cbLight3;
	ComPtr<ID3D11Buffer>	m_pConstantBufferLight[g_iMaxLight];
	GLightObj				m_PointLight[g_iMaxLight];
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	bool		DrawDebug();
	//--------------------------------------------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
public:
	GProjMain(void);
	virtual ~GProjMain(void);
};


//#pragma once
//#include "TBasisLib_2.h"
//#include "THeightMap.h"
//#include "TBoxObj.h"
//#include "TLightobj.h"
//
//T_STR TechniqueName[] =
//{ 	
//   _T("SpecularLighting"),   
//   _T("VSLightingColor"),   
//   _T("PSLightingColor"),
//   
//};
//
//struct VS_CONSTANT_BUFFER
//{
//	D3DXVECTOR4		vLightPosition[3];	
//	D3DXVECTOR4		vLightColor[3];
//};
//
//class GProjMain : public TBasisLib_2
//{
//public:
//	TBoxObj					m_BoxObj;
//	THeightMap				m_HeightMap;
//	
//	TLightObj				m_SunLight;
//	TLightObj				m_PointLight[3];
//
//	TLineShape				m_LineDraw;	
//	int						m_iTechniqueCnt;
//
//	ID3D11Buffer*			m_pConstantBuffer;
//	HRESULT					CreateConstantBuffer();
//public:		
//	bool		Init();
//	bool		Frame();
//	bool		Render();
//	bool		Release();
//	bool		DrawDebug(bool bDrawString = true, bool bDrawLine=true);
//	//--------------------------------------------------------------------------------------
//	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
//	//--------------------------------------------------------------------------------------
//	HRESULT		CreateResource();
//	HRESULT		DeleteResource();	
//public:
//	GProjMain(void);
//	~GProjMain(void);
//};
