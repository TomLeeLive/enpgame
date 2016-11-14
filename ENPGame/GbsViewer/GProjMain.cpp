#include "GProjMain.h"

GProjMain* g_pMain;

void GProjMain::AddObject()
{
	if (!m_tObj.Load(GetDevice(), _T("../../data/Turret_Deploy.tbs"), L"../../data/shader/box.hlsl"))
	{
		return;
	}
	m_tObj.m_pModelList[m_tObj.m_pModelList.size() - 1]->m_pModel->m_matWorld._41 = 
		m_tObj.m_pModelList.size() * 30.0f;
}
bool GProjMain::Init()
{
	m_tbsobj.Init();	
	//if(!m_tbsobj.Load(GetDevice(),_T("data/turret.GBS"), L"data/shader/box.hlsl")  )
	//if (!m_tbsobj.Load(GetDevice(), _T("data/object/dropship/dropship_land.GBS"), L"data/shader/box.hlsl"))
	//if (!m_tbsobj.Load(GetDevice(), _T("data/object/dropship/dropship_fly.GBS"), L"data/shader/box.hlsl"))
	//if (!m_tbsobj.Load(GetDevice(), _T("data/object/shuttle/shuttle.GBS"), L"data/shader/box.hlsl"))
	//if (!m_tbsobj.Load(GetDevice(), _T("data/object/ship/spaceship.GBS"), L"data/shader/box.hlsl"))
	//if (!m_tbsobj.Load(GetDevice(), _T("data/object/car/car.GBS"), L"data/shader/box.hlsl"))
	//if (!m_tbsobj.Load(GetDevice(), _T("data/object/mars/mars.GBS"), L"data/shader/box.hlsl"))
	//if (!m_tbsobj.Load(GetDevice(), _T("data/object/lab/lab.GBS"), L"data/shader/box.hlsl"))
	if (!m_tbsobj.Load(GetDevice(), _T("data/object/fps_shotgun/shotgun3.GBS"), L"data/shader/box.hlsl"))
	{
		return false;
	}

	//m_tObj.Init();
	//if (!m_tObj.Load(GetDevice(), _T("data/turret.GBS"), L"data/shader/box.hlsl"))
	//{
	//	return false;
	//}
	//m_tObj.m_matWorld._41 = -30.0f;


	//--------------------------------------------------------------------------------------
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------	
	m_pMainCamera = make_shared<GModelViewCamera>();
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 100.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	float fAspectRatio = m_iWindowWidth / (FLOAT)m_iWindowHeight;
	m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 10000.0f);
	m_pMainCamera->SetWindow(m_iWindowWidth, m_iWindowHeight);
	
	return true;
}
bool GProjMain::Render()
{	
	m_tbsobj.SetMatrix(NULL, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	m_tbsobj.Render(m_pImmediateContext);

	m_tObj.SetMatrix(NULL, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	m_tObj.Render(m_pImmediateContext);
	return true;
}
bool GProjMain::Release()
{
	m_tbsobj.Release();
	return true;
}

bool GProjMain::Frame()
{	
	m_pMainCamera->Update(g_fSecPerFrame);
	m_matWorld = *m_pMainCamera->GetWorldMatrix();
	m_tbsobj.Frame();	
		
	if (I_Input.KeyCheck(DIK_F4) == KEY_UP)
	{		
		AddObject();
	}
	m_tObj.Frame();

	return true;
}

HRESULT GProjMain::CreateResource()
{
	HRESULT hr;
	if (m_pMainCamera)
	{
		float fAspectRatio = m_SwapChainDesc.BufferDesc.Width /
			(float)m_SwapChainDesc.BufferDesc.Height;
		m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 500.0f);
	}
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
GCORE_RUN(GBS Viewer);

