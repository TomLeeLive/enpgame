#include "_stdafx.h"

GProjMain* g_pMain;

bool GProjMain::Init()
{


	// 메인 카메라 뷰 행렬 세팅
	SAFE_NEW(m_pMainCamera, GCamera);
	float fAspectRatio = g_pMain->m_iWindowWidth / (FLOAT)g_pMain->m_iWindowHeight;
	m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 10000.0f);
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 10.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	m_pMainCamera->SetWindow(g_pMain->m_iWindowWidth, g_pMain->m_iWindowHeight);

	//m_EffManager.Init();

	
	T_STR strFile = L"fire.eff";
	I_EffMgr.Load(&strFile, L"data/shader/plane.hlsl");
	return true;
}
bool GProjMain::Frame()
{
	//--------------------------------------------------------------------------------------
	// 엔진에 있는 뷰 및 투영 행렬 갱신
	//--------------------------------------------------------------------------------------
	m_pMainCamera->Frame();

	I_EffMgr.Frame(m_pMainCamera,&m_Timer);

	if (I_Input.KeyCheck(DIK_F) == KEY_PUSH) {

		KEffect* eff = I_EffMgr.GetPtr(L"fire.eff");
		auto Effect = make_shared<KEffectObj>();
		Effect->Set(eff, 0.0f, 100.0f);
		Effect->Init();
		//Effect->m_pEffect->m_pSprite->m_bLoop = false;
		I_EffMgr.m_List.push_back(Effect);
	}




	return true;
}
bool GProjMain::Render()
{
	//D3DXMATRIX matTrans, matRotation, matZ;

	// 2초당 1회전( 1 초 * D3DX_PI = 3.14 )
	//float t = m_Timer.GetElapsedTime() * D3DX_PI;


	I_EffMgr.Render();


	return true;
}
bool GProjMain::Release()
{
	SAFE_ZERO(m_pMainCamera);

	I_EffMgr.Release();

	return true;
}

//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GProjMain::CreateResource()
{
	HRESULT hr;

	I_EffMgr.CreateResource(&m_SwapChainDesc);

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