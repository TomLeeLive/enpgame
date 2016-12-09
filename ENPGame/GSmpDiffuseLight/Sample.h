#pragma once
#include "TBasisLib_0.h"
#include "TShape.h"
#include "TCamera.h"
#include "TBoxObj.h"
#include "map/THeightMap.h"

struct LIGHT_CONSTANT_BUFFER
{
	D3DXMATRIX			g_matInvWorld;
	// Material
	D3DXVECTOR4			g_cAmbientMaterial;
	D3DXVECTOR4			g_cDiffuseMaterial;
	D3DXVECTOR4			g_cSpecularMaterial;
	D3DXVECTOR4			g_cEmissionMaterial;
	// Light
	D3DXVECTOR4			g_cAmbientLightColor;
	D3DXVECTOR4			g_cDiffuseLightColor;
	D3DXVECTOR4			g_cSpecularLightColor;
	D3DXVECTOR4			g_vLightDir; // w = light damping(attenuation) : 감쇠
	D3DXVECTOR4			g_vLightPos; // w = light radius
	D3DXVECTOR4			g_vEyeDir;// w = light intensity : 강도
	D3DXVECTOR4			g_vEyePos;// w = light radius	
};

class Sample : public TBasisLib_0
{
public:
	THeightMap		m_HeightMap;
	TLineShape		m_LineDraw;
	shared_ptr<TCamera > m_pMainCamera;
	TBoxObj			m_SphereObj;
	D3DXVECTOR3		m_vLightVector;
	LIGHT_CONSTANT_BUFFER m_cbLight;
	ComPtr<ID3D11Buffer>	m_pConstantBufferLight;
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
	Sample(void);
	virtual ~Sample(void);
};
