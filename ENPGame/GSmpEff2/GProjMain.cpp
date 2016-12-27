#include "_stdafx.h"


bool GProjMain::Init()
{
	m_pPS.Attach(DX::LoadPixelShaderFile(g_pd3dDevice,
		L"data/shader/Blend.hlsl", "PS_MATERIAL"));
	//--------------------------------------------------------------------------------------
	// 배경 부분
	//--------------------------------------------------------------------------------------
	m_pScreen = make_shared<GPlaneShape>();
	if (m_pScreen->Create(g_pd3dDevice, L"data/shader/plane.hlsl") == false)
	{
		MessageBox(0, _T("m_pPlane 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	//SAFE_NEW(m_pSprite, GSprite);
	m_pSprite = make_shared<GSprite>();
	//---------------------------------------------------------------------------------
	// 월드  행렬
	//---------------------------------------------------------------------------------
	D3DXMATRIX matRotation, matScale;
	D3DXMatrixScaling(&matScale, 5.0f, 5.0f, 5.0f);
	D3DXMatrixRotationX(&matRotation, D3DX_PI*0.5f);
	D3DXMatrixMultiply(&m_mPlanWorld, &matScale, &matRotation);
	D3DXMatrixIdentity(&m_matPlaneWorld);


	//play 버튼시 init() 부분
	m_pSprite.get()->Create(g_pd3dDevice, L"data/shader/plane.hlsl", L"data/effect/ds1.dds");
	// 애니메이션 관련, 가로4x4
	m_pSprite.get()->SetRectAnimation(1.0f, 4, 128, 4, 128);
	return true;
};
bool GProjMain::Frame()
{
	//--------------------------------------------------------------------------------
	// 빌보드 행렬
	//--------------------------------------------------------------------------------
	FLOAT fDeterminant;
	D3DXMATRIX matBillboard;
	D3DXMatrixInverse(&matBillboard, &fDeterminant, m_pCamera->GetViewMatrix());
	matBillboard._41 = 0.0f;
	matBillboard._42 = 0.0f;
	matBillboard._43 = 0.0f;
	matBillboard._44 = 1.0f;


	m_pSprite.get()->SetMatrix(&matBillboard, m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
	m_pSprite.get()->Frame(g_pImmediateContext,m_Timer.GetElapsedTime(), g_fSecPerFrame);
	return true;
};
bool GProjMain::Render()
{
	D3DXVECTOR4 vColor = D3DXVECTOR4(0, 0, 0, 0);
	float fValue = cosf(m_Timer.GetElapsedTime())*0.5f + 0.5f;
	FLOAT fFactor[4] = { 0 , };
	m_vMaterial.x = 1.0f;
	m_vMaterial.y = 1.0f;
	m_vMaterial.z = 1.0f;
	m_vMaterial.w = fValue;
	m_pSprite.get()->m_cbData.Color = m_vMaterial;
	ApplyBS(g_pImmediateContext, GDxState::g_pBSAlphaOne, fFactor, 0xffffffff);

	//if (m_RT.Begin(g_pImmediateContext, vColor))
	//	{
	//ApplyRS(g_pMain->GetContext(), GDxState::g_pRSBackCullSolid);
	//ApplyDSS(g_pMain->GetContext(), GDxState::g_pDSSDepthEnable);

	D3DXMATRIX matEffectWld;
	D3DXMatrixIdentity(&m_matWorld);
	matEffectWld = m_matWorld;
	matEffectWld._42 = 10.0f;

	m_pSprite.get()->SetMatrix(&matEffectWld, m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
	m_pSprite.get()->Render(g_pImmediateContext);

	//	m_RT.Apply(g_pImmediateContext, GetRenderTargetView(), GetDepthStencilView());
	//	m_RT.End(g_pImmediateContext);
	//	}

	//ApplyDSS(g_pMain->GetContext(), GDxState::g_pDSSDepthDisable);
	D3DXMATRIX matIdentity;
	D3DXMatrixIdentity(&matIdentity);
	m_pScreen->SetMatrix(&matIdentity, &matIdentity, &matIdentity);
	m_pScreen->PreRender(g_pImmediateContext);
	g_pImmediateContext->OMSetBlendState(GDxState::g_pBSAlphaOne, 0, -1);
	//	g_pImmediateContext->PSSetShaderResources(0, 1, m_RT.m_pSRV.GetAddressOf());
	g_pImmediateContext->PSSetShader(m_pPS.Get(), NULL, 0);
	g_pImmediateContext->PSSetConstantBuffers(0, 1, m_pSprite.get()->m_dxobj.g_pConstantBuffer.GetAddressOf());
	m_pScreen->PostRender(g_pImmediateContext);




	//ApplyDSS(g_pImmediateContext, GDxState::g_pDSSDepthDisable);
	//ApplyBS(g_pImmediateContext, GDxState::g_pBSOneZero);

	ClearD3D11DeviceContext(g_pImmediateContext);
	return true;
};
bool GProjMain::Release()
{
	return true;
};
HRESULT GProjMain::CreateResource()
{
	HRESULT hr;
	return S_OK;
}
HRESULT GProjMain::DeleteResource()
{
	HRESULT hr;
	return S_OK;
}
GProjMain::GProjMain()
{
}


GProjMain::~GProjMain()
{
}
int GProjMain::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera != nullptr)
	{
		m_pCamera->WndProc(hWnd, msg, wParam, lParam);
	}
	return -1;
}