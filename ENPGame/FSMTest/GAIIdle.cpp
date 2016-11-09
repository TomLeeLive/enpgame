#include "_stdafx.h"

GAIIdle * GAIIdle::pInstance_ = 0;

bool GAIIdle::Init()
{
	//--------------------------------------------------------------------------------------
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------	
	m_pMainCamera = make_shared<GCamera>();
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(10.0f, 10.0f, -10.0f), D3DXVECTOR3(-10.0f, 10.0f, 50.0f));

	float fAspectRatio = g_pMain->m_iWindowWidth / (FLOAT)g_pMain->m_iWindowHeight;
	m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 10000.0f);
	m_pMainCamera->SetWindow(g_pMain->m_iWindowWidth, g_pMain->m_iWindowHeight);

	/*SAFE_NEW(m_Box1, GBoxShape);
	m_Box1->Create(m_pd3dDevice, L"data/shader/box.hlsl", L"data/flagstone.bmp");*/

	/*SAFE_NEW(m_Box2, GBoxShape);
	m_Box2->Create(m_pd3dDevice, L"data/shader/box.hlsl", L"data/flagstone.bmp");

	SAFE_NEW(m_Box3, GBoxShape);
	m_Box3->Create(m_pd3dDevice, L"data/shader/box.hlsl", L"data/flagstone.bmp");

*/

	return true;
}
bool GAIIdle::Frame()
{
	m_pMainCamera->Frame();
	m_matWorld = *m_pMainCamera->GetWorldMatrix();
	m_matWorld._41 = 0.0f;
	m_matWorld._42 = 0.0f;
	m_matWorld._43 = 0.0f;

	m_pMainCamera->Frame();
	D3DXMatrixIdentity(&m_matWorld);
	/*m_Box1->SetMatrix(&m_matWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);*/

	return true;
}
bool GAIIdle::Render()
{
	/*m_Box1->Render(m_pImmediateContext);*/
	return true;
}
bool GAIIdle::Release()
{
	return true;
}
HRESULT GAIIdle::CreateResource()
{
	HRESULT hr;

	//if (m_pMainCamera != nullptr)
	//	m_pMainCamera->SetProjMatrix((float)D3DX_PI * 0.25f,
	//		m_SwapChainDesc.BufferDesc.Width / (FLOAT)m_SwapChainDesc.BufferDesc.Height, 1.0f, 10000.0f);
	{
		float fAspectRatio = g_pMain->m_SwapChainDesc.BufferDesc.Width /
			(float)g_pMain->m_SwapChainDesc.BufferDesc.Height;
		m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 500.0f);
	}
	return S_OK;
}
HRESULT GAIIdle::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIIdle::GAIIdle()
{
	pInstance_ = 0;
}


GAIIdle::~GAIIdle()
{
}
int GAIIdle::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainCamera != nullptr)
	{
		m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	}
	return -1;
}

