#include "stdafx.h"
#include "_stdafx.h"

bool		KEffect::Init() { 
	m_pPS.Attach(DX::LoadPixelShaderFile(g_pd3dDevice, L"data/shader/Blend.hlsl", "PS_MATERIAL"));
	//--------------------------------------------------------------------------------------
	// 배경 부분
	//--------------------------------------------------------------------------------------
	m_pScreen = make_shared<GPlaneShape>();
	if (m_pScreen->Create(g_pd3dDevice, L"data/shader/plane.hlsl") == false)
	{
		MessageBox(0, _T("m_pPlane 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}

	m_pSprite = make_shared<GSprite>();
	//SAFE_NEW(m_pSprite, GSprite);
	//--------------------------------------------------------------------------------------
	// 월드  행렬
	//--------------------------------------------------------------------------------------
	D3DXMATRIX matRotation, matScale;
	D3DXMatrixScaling(&matScale, 5.0f, 5.0f, 5.0f);
	D3DXMatrixRotationX(&matRotation, D3DX_PI*0.5f);
	D3DXMatrixMultiply(&m_mPlanWorld, &matScale, &matRotation);
	D3DXMatrixIdentity(&m_matPlaneWorld);
	
	
	return true; };;;;;;;;;;;;;;;;;;;;;;;;;
bool		KEffect::Frame(GCamera* camera, GTimer* timer) {
	if (m_pSprite == NULL)
		return false;

	//m_matWorld = *(camera->GetWorldMatrix());
	//--------------------------------------------------------------------------------------
	// 빌보드 행렬
	//-----------------------------------------------------------------------------------
	FLOAT fDeterminant;
	//m_matBillboard;
	D3DXMatrixInverse(&m_matBillboard, &fDeterminant, camera->GetViewMatrix());
	m_matBillboard._41 = 0.0f;
	m_matBillboard._42 = 0.0f;
	m_matBillboard._43 = 0.0f;
	m_matBillboard._44 = 1.0f;

	D3DXMATRIX matView = *(camera->GetViewMatrix());
	D3DXMATRIX matProj = *(camera->GetProjMatrix());
	m_pSprite->SetMatrix(&m_matBillboard, &matView, &matProj);
	m_pSprite->Frame(g_pImmediateContext, timer->GetElapsedTime(), g_fSecPerFrame);
	




	D3DXVECTOR4 vColor = D3DXVECTOR4(0, 0, 0, 0);
	float fValue = cosf(timer->GetElapsedTime())*0.5f + 0.5f;
	FLOAT fFactor[4] = { 0 , };
	m_vMaterial.x = 1.0f;
	m_vMaterial.y = 1.0f;
	m_vMaterial.z = 1.0f;
	m_vMaterial.w = fValue;
	m_pSprite->m_cbData.Color = m_vMaterial;

	ApplyBS(g_pImmediateContext, GDxState::g_pBSAlphaOne, fFactor, 0xffffffff);


	return true; };
bool		KEffect::Render() {

	if (m_pSprite == NULL)
		return false;

	//if (m_RT.Begin(m_pImmediateContext, vColor))
	//	{
	ApplyRS(g_pImmediateContext, GDxState::g_pRSBackCullSolid);
	ApplyDSS(g_pImmediateContext, GDxState::g_pDSSDepthEnable);

	if (m_bCheck == true)
	{
		RenderPlane();
	}

	//	m_RT.Apply(m_pImmediateContext, GetRenderTargetView(), GetDepthStencilView());
	//	m_RT.End(m_pImmediateContext);
	//	}

	ApplyDSS(g_pImmediateContext, GDxState::g_pDSSDepthDisable);
	D3DXMATRIX matIdentity;
	D3DXMatrixIdentity(&matIdentity);
	m_pScreen->SetMatrix(&matIdentity, &matIdentity, &matIdentity);
	m_pScreen->PreRender(g_pImmediateContext);
	g_pImmediateContext->OMSetBlendState(GDxState::g_pBSAlphaOne, 0, -1);
	//	m_pImmediateContext->PSSetShaderResources(0, 1, m_RT.m_pSRV.GetAddressOf());
	g_pImmediateContext->PSSetShader(m_pPS.Get(), NULL, 0);
	g_pImmediateContext->PSSetConstantBuffers(0, 1, m_pSprite->m_dxobj.g_pConstantBuffer.GetAddressOf());
	m_pScreen->PostRender(g_pImmediateContext);

	return true; };
bool		KEffect::Release() { 
	SAFE_RELEASE(m_pSprite);
	return true;
};

//창이 사이즈가 변경이되면 호출이 됨.
HRESULT		KEffect::CreateResource(DXGI_SWAP_CHAIN_DESC*	SwapChainDesc) { return S_OK; }

HRESULT		KEffect::DeleteResource() { return S_OK; }

bool KEffect::RenderPlane()
{
	if (m_pSprite == NULL)
		return false;

	m_pSprite->Render(g_pImmediateContext);
	return true;
}


KEffect::KEffect()
{
	D3DXMatrixIdentity(&m_matBillboard);
	m_type = G_EFFECT_BULLET;
	m_fPlayTime = 0.0f;
	m_pSprite = NULL;
	m_bCheck = false;
}


KEffect::~KEffect()
{
}
