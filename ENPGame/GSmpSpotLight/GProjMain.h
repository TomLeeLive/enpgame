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
	D3DXVECTOR4			g_vLightDir[g_iNumLight]; // w = light damping(attenuation) : 감쇠
	D3DXVECTOR4			g_vLightPos[g_iNumLight]; // w = light radius
	D3DXVECTOR4			g_vEyeDir[g_iNumLight];// w = light intensity : 강도
	D3DXVECTOR4			g_vEyePos[g_iNumLight];// w = light radius		
};
struct LIGHT_CONSTANT_BUFFER3
{
	D3DXVECTOR4			g_vSpotInfo[g_iNumLight];
	//float				g_fFalloff;		// 내부 콘과 외부 콘의 휘도( Luminance )
	//float				g_fTheta;		// 내부 콘의 각도 범위		
	//float				g_fPhi;			// 외부 콘의 각도 범위
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
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
public:
	GProjMain(void);
	virtual ~GProjMain(void);
};

