//#include "stdafx.h"
//#include "_stdafx.h"
#include "KEffect.h"
bool		KEffect::Init() { 
	//EnterCriticalSection(&g_CSd3dDevice);
	m_pPS.Attach(DX::LoadPixelShaderFile(g_pd3dDevice, L"data/shader/Blend.hlsl", "PS_MATERIAL"));
	//LeaveCriticalSection(&g_CSd3dDevice);

	//--------------------------------------------------------------------------------------
	// 배경 부분
	//--------------------------------------------------------------------------------------
	m_pScreen = make_shared<GPlaneShape>();

	//EnterCriticalSection(&g_CSd3dDevice);
	if (m_pScreen->Create(g_pd3dDevice, L"data/shader/plane.hlsl") == false)
	{
		//LeaveCriticalSection(&g_CSd3dDevice);
		MessageBox(0, _T("m_pPlane 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	//LeaveCriticalSection(&g_CSd3dDevice);

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
	
	
	return true; }
bool		KEffect::PreFrame(GCamera* camera, GTimer* timer) {
	m_pCamera = camera;
	m_pTimer = timer;
	return true;
}
bool		KEffect::Frame() {
	if (m_pSprite == NULL)
		return false;

	//m_matWorld = *(camera->GetWorldMatrix());
	//--------------------------------------------------------------------------------------
	// 빌보드 행렬
	//-----------------------------------------------------------------------------------
	FLOAT fDeterminant;
	//m_matBillboard;
	D3DXMatrixInverse(&m_matBillboard, &fDeterminant, m_pCamera->GetViewMatrix());
	m_matBillboard._41 = 0.0f;
	m_matBillboard._42 = 0.0f;
	m_matBillboard._43 = 0.0f;
	m_matBillboard._44 = 1.0f;

	D3DXMATRIX matView = *(m_pCamera->GetViewMatrix());
	D3DXMATRIX matProj = *(m_pCamera->GetProjMatrix());
	m_pSprite->SetMatrix(&m_matBillboard, &matView, &matProj);

	//EnterCriticalSection(&g_CSImmediateContext);
	m_pSprite->Frame(g_pImmediateContext, m_pTimer->GetElapsedTime(), g_fSecPerFrame);
	//LeaveCriticalSection(&g_CSImmediateContext);




	D3DXVECTOR4 vColor = D3DXVECTOR4(0, 0, 0, 0);
	float fValue = cosf(m_pTimer->GetElapsedTime())*0.5f + 0.5f;
	FLOAT fFactor[4] = { 0 , };
	m_vMaterial.x = 1.0f;
	m_vMaterial.y = 1.0f;
	m_vMaterial.z = 1.0f;
	m_vMaterial.w = fValue;
	m_pSprite->m_cbData.Color = m_vMaterial;

	//EnterCriticalSection(&g_CSImmediateContext);
	ApplyBS(g_pImmediateContext, GDxState::g_pBSAlphaOne, fFactor, 0xffffffff);
	//LeaveCriticalSection(&g_CSImmediateContext);

	return true; };
bool		KEffect::Render(ID3D11DeviceContext*		pContext) {

	if (m_pSprite == NULL)
		return false;

	//if (m_RT.Begin(m_pImmediateContext, vColor))
	//	{
	//EnterCriticalSection(&g_CSImmediateContext);
	ApplyRS(g_pImmediateContext, GDxState::g_pRSBackCullSolid);
	ApplyDSS(g_pImmediateContext, GDxState::g_pDSSDepthEnable);
	//LeaveCriticalSection(&g_CSImmediateContext);

	if (m_bCheck == true)
	{
		RenderPlane();
	}

	//	m_RT.Apply(m_pImmediateContext, GetRenderTargetView(), GetDepthStencilView());
	//	m_RT.End(m_pImmediateContext);
	//	}

	//EnterCriticalSection(&g_CSImmediateContext);
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
	//LeaveCriticalSection(&g_CSImmediateContext);

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

	//EnterCriticalSection(&g_CSImmediateContext);
	m_pSprite->Render(g_pImmediateContext);
	//LeaveCriticalSection(&g_CSImmediateContext);

	return true;
}
void KEffect::SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj)
{
	if (pWorld != NULL)
	{
		m_matWorld = *pWorld;
		m_vCenter.x = pWorld->_41;
		m_vCenter.y = pWorld->_42;
		m_vCenter.z = pWorld->_43;
	}
	if (pView != NULL)
	{
		m_matView = *pView;
	}
	if (pProj != NULL)
	{
		m_matProj = *pProj;
	}
	//D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld);
	//D3DXMatrixTranspose(&m_cbData.matView, &m_matView);
	//D3DXMatrixTranspose(&m_cbData.matProj, &m_matProj);
}

KEffect::KEffect()
{
	m_vCenter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);

	D3DXMatrixIdentity(&m_matBillboard);
	m_type = G_EFFECT_BULLET;
	m_fPlayTime = 0.0f;
	m_pSprite = NULL;
	m_bCheck = false;
}


KEffect::~KEffect()
{
}
