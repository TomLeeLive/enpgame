#pragma once
#include "TBasisLib_0.h"
#include "TShape.h"
#include "map/THeightMap.h"
#include "TCamera.h"
#include "TBoxObj.h"
#include "TLightObj.h"

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

class Sample : public TBasisLib_0
{
public:
	THeightMap		m_HeightMap;
	TLineShape		m_LineDraw;
	shared_ptr<TCamera > m_pMainCamera;
	TBoxObj			m_SphereObj;
	D3DXVECTOR3		m_vLightVector;
	LIGHT_CONSTANT_BUFFER1   m_cbLight1;
	LIGHT_CONSTANT_BUFFER2   m_cbLight2;
	LIGHT_CONSTANT_BUFFER3   m_cbLight3;
	ComPtr<ID3D11Buffer>	m_pConstantBufferLight[g_iMaxLight];
	TLightObj				m_PointLight[g_iMaxLight];
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
	Sample(void);
	virtual ~Sample(void);
};

