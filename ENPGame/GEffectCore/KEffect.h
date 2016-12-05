#pragma once
#include "GDxState.h"
#include "GCamera.h"

#include "GSprite.h"
#include "GTimer.h"
#include "GCamera.h"

using namespace DX;

enum G_EFFECT_TYPE {
	G_EFFECT_BULLET = 0,
	G_EFFECT_BLOOD,
	G_EFFECT_DUST,
	G_EFFECT_SMOG,
	G_EFFECT_CNT
};

class KEffect
{
public:
	G_EFFECT_TYPE				m_type;
	float						m_fPlayTime;
	bool						m_bCheck;
	GPlaneShape					m_BigPlane;
	shared_ptr<GSprite>			m_pSprite;
	ComPtr<ID3D11PixelShader>	m_pPS;
	D3DXVECTOR4					m_vMaterial;
	D3DXMATRIX					m_matPlaneWorld;
	D3DXMATRIX					m_mPlanWorld;
	D3DXMATRIX					m_matBillboard;
	//D3DXMATRIX					m_matWorld;
	shared_ptr<GPlaneShape>		m_pPlane;
	shared_ptr<GPlaneShape>		m_pScreen;
	bool RenderPlane();
public:
	virtual bool		Init();
	virtual bool		Frame(GCamera* camera, GTimer* timer);
	virtual bool		Render();
	virtual bool		Release();
	//--------------------------------------------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//--------------------------------------------------------------------------------------
	virtual HRESULT		CreateResource(DXGI_SWAP_CHAIN_DESC*	SwapChainDesc);
	virtual HRESULT		DeleteResource();

	KEffect();
	virtual ~KEffect();
};

