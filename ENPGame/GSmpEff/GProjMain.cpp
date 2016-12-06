#include "_stdafx.h"

GProjMain* g_pMain;

bool GProjMain::Init()
{


	// ���� ī�޶� �� ��� ����
	SAFE_NEW(m_pMainCamera, GCamera);
	float fAspectRatio = g_pMain->m_iWindowWidth / (FLOAT)g_pMain->m_iWindowHeight;
	m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 10000.0f);
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 10.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	m_pMainCamera->SetWindow(g_pMain->m_iWindowWidth, g_pMain->m_iWindowHeight);

	//m_EffManager.Init();

	
	T_STR strFile = L"fire.eff";
	m_EffManager.Load(&strFile);
	return true;
}
bool GProjMain::Frame()
{
	//--------------------------------------------------------------------------------------
	// ������ �ִ� �� �� ���� ��� ����
	//--------------------------------------------------------------------------------------
	m_pMainCamera->Frame();

	m_EffManager.Frame(m_pMainCamera,&m_Timer);
	return true;
}
bool GProjMain::Render()
{
	//D3DXMATRIX matTrans, matRotation, matZ;

	// 2�ʴ� 1ȸ��( 1 �� * D3DX_PI = 3.14 )
	//float t = m_Timer.GetElapsedTime() * D3DX_PI;


	m_EffManager.Render();


	return true;
}
bool GProjMain::Release()
{
	SAFE_ZERO(m_pMainCamera);

	m_EffManager.Release();

	return true;
}

//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GProjMain::CreateResource()
{
	HRESULT hr;

	m_EffManager.CreateResource(&m_SwapChainDesc);

	return S_OK;
}
//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GProjMain::DeleteResource()
{
	HRESULT hr = S_OK;
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	return S_OK;
}
GProjMain::GProjMain(void)
{
	SAFE_ZERO(m_pMainCamera);
}

GProjMain::~GProjMain(void)
{
}

int GProjMain::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainCamera != nullptr)
	{
		m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	}
	return -1;
}

GCORE_RUN(L"GBasisSample UI_0");