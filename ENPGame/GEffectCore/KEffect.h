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
	D3DXVECTOR3					m_vCenter;
	D3DXMATRIX					m_matWorld;
	D3DXMATRIX					m_matView;
	D3DXMATRIX					m_matProj;

	GCamera*					m_pCamera;
	GTimer*						m_pTimer;
	T_STR						m_szDirName;
	T_STR						m_szName;

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

	virtual void				SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);
public:
	virtual bool		Init();
	virtual bool		PreFrame(GCamera* camera, GTimer* timer);
	virtual bool		Frame();
	virtual bool		Render(ID3D11DeviceContext*		pContext);
	virtual bool		Release();
	//--------------------------------------------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//--------------------------------------------------------------------------------------
	virtual HRESULT		CreateResource(DXGI_SWAP_CHAIN_DESC*	SwapChainDesc);
	virtual HRESULT		DeleteResource();

	KEffect();
	virtual ~KEffect();
};

class KEffectObj {
public:
	bool    m_bStart;
	bool	m_bEnd;
	bool	m_bLoop;
	KEffect* m_pEffect;
	float	m_fStartTime;
	float   m_fElapsedTime;
	int		 m_iStartFrame;
	int		 m_iLastFrame;
	//int		 m_iCurrentFrame;
	//float	 m_fFrame;
	//float	 m_fLerpTime;
	float	 m_fSpeed;

	int		m_iApplyIndex;
	float	m_fTime;

	virtual bool		Init() { return true; };
	virtual bool		PreFrame(GCamera* camera, GTimer* timer) {
		m_pEffect->PreFrame(camera, timer);
		return true;
	};
	virtual bool		Frame() {


		//시작시간.
		if (m_bStart) {
			m_fStartTime = m_pEffect->m_pTimer->GetElapsedTime();
			m_bStart = false;

			m_pEffect->m_pSprite->m_fTime = 0.0f;
			m_pEffect->m_pSprite->m_iApplyIndex = 0;
			m_pEffect->m_pSprite->m_fAnimTime = 0.0f;
			m_pEffect->m_pSprite->m_fLifeTime = 0.0f;
			m_pEffect->m_pSprite->m_fElapseTime = 0.0f;

			m_pEffect->m_pSprite->m_fAnimTime = 0.0f;
			m_pEffect->m_pSprite->m_fLifeTime = 0.0f;
			m_pEffect->m_pSprite->m_fElapseTime = 0.0f;
			m_pEffect->m_pSprite->m_bInstancing = false;
			m_pEffect->m_pSprite->m_BlendType = 0;
			m_pEffect->m_pSprite->m_fTime = 0.0f;
			m_pEffect->m_pSprite->m_iApplyIndex = 0;
			m_pEffect->m_pSprite->m_fSecPerRender = 0.2f;
			//m_pEffect->m_pSprite->m_iNumTexture = 0;
			m_pEffect->m_pSprite->m_RectSet.left = 4;
			m_pEffect->m_pSprite->m_RectSet.right = 64; // 텍스쳐 가로 셋 갯수 및 크기	
			m_pEffect->m_pSprite->m_RectSet.top = 4;
			m_pEffect->m_pSprite->m_RectSet.bottom = 64; // 텍스쳐 세로 셋 갯수 및 크기
		}


		//경과시간.
		m_fElapsedTime = m_pEffect->m_pTimer->GetElapsedTime() - m_fStartTime;

		/*
		if (m_pChar->m_iAniLoop != 0 || m_fFrame < m_iLastFrame - 1)
		{
		if (m_pBoneObject->AniFrame(m_fFrame,
		m_fLerpTime,
		m_iStartFrame,
		m_iLastFrame,
		m_pMatrix))
		{
		m_iCurrentFrame = m_iStartFrame;
		m_fFrame = (float)m_iStartFrame + m_fLerpTime;
		}
		}
		*/

		if (m_pEffect->m_pTimer->GetElapsedTime() >= m_pEffect->m_pSprite->m_fSecPerRender)
		{

			if (++m_iApplyIndex >= m_pEffect->m_pSprite->m_iNumTexture) {
				if (true == m_bLoop)
					m_iApplyIndex = 0;
				else {
					m_iApplyIndex--;
					m_bEnd = true;
					return false;
				}
			}

			if (true == m_bLoop)
				m_fElapsedTime = 0.0f;
		}
		//m_pEffect->m_pSprite->m_fElapseTime = m_fElapsedTime;
		m_pEffect->m_pSprite->Updata(g_pImmediateContext, m_fElapsedTime, m_iApplyIndex, m_pEffect->m_pTimer->GetElapsedTime(), g_fSecPerFrame);
		//Updata(pContext, m_fTime, m_iApplyIndex, fGlobalTime, fElapsedTime);

		m_pEffect->m_pSprite->Frame(g_pImmediateContext, m_pEffect->m_pTimer->GetElapsedTime(), g_fSecPerFrame);
		m_pEffect->Frame();
		return true;
	};
	virtual bool		Render(ID3D11DeviceContext*		pContext) {
		if (!m_bEnd)
			m_pEffect->Render(pContext);
		return true;
	};
	virtual bool		Release() { return true; };
	virtual bool		Set(KEffect* pEffect, float fStart, float fEnd) {
		m_pEffect = pEffect;
		m_iStartFrame = fStart;
		m_iLastFrame = fEnd;
		return true;
	}
	//--------------------------------------------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//--------------------------------------------------------------------------------------
	virtual HRESULT		CreateResource(DXGI_SWAP_CHAIN_DESC*	SwapChainDesc) { return S_OK; };
	virtual HRESULT		DeleteResource() { return S_OK; };
public:
	KEffectObj() {
		m_bStart = true;
		m_bEnd = false;
		m_bLoop = false;
		m_fTime = 0.0f;
		m_iApplyIndex = 0;

		m_iStartFrame = 0;
		m_iLastFrame = 0;

		m_fSpeed = 1.0f;

		m_fStartTime = 0.0f;
		m_fElapsedTime = 0.0f;

	};
	virtual ~KEffectObj() {};
};