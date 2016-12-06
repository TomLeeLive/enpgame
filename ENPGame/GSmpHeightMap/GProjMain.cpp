#include "_stdafx.h"

GProjMain* g_pMain;

bool GProjMain::Init()
{
	HRESULT hr;
	//카메라 생성
	SAFE_NEW(m_pMainCamera, GCamera);

	D3DXVECTOR3 vTargetPosition = D3DXVECTOR3(0.0f, -0.1f, 100.0f);
	D3DXVECTOR3 vUpVector(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 vCameraPosition = D3DXVECTOR3(0.0f, 10.0f, -50.1f);
	// 메인 카메라 뷰 행렬 세팅
	m_pMainCamera->SetViewMatrix(vCameraPosition, vTargetPosition, vUpVector);

	m_pMainCamera->SetProjMatrix(D3DX_PI * 0.25f,
		m_SwapChainDesc.BufferDesc.Width / (float)(m_SwapChainDesc.BufferDesc.Height),
		0.1f, 10000.0f);


	//HeightMap
	m_HeightMap.Init(m_pd3dDevice, m_pImmediateContext);
	if (FAILED(m_HeightMap.CreateHeightMap(L"data/HeightTest.bmp")))
	{
		return false;
	}

	m_HeightMap.m_bStaticLight = true;
	TMapDesc MapDesc = {
		m_HeightMap.m_iNumRows,	m_HeightMap.m_iNumCols,
		//5,5,
		1.0f, 1.0f,
		L"data/Sand.jpg",
		L"data/shader/CustomizeMap.hlsl" };

	if (!m_HeightMap.Load(MapDesc))
	{
		return false;
	}

	//TMapDesc MapDescCustom;
	////CustomizeMap
	//MapDescCustom = { 5, 5, 1.0f, 0.1f,L"data/castle.jpg", L"data/shader/CustomizeMap.hlsl" };
	//m_CustomMap.Init(GetDevice(), m_pImmediateContext);
	//if (FAILED(m_CustomMap.Load(MapDescCustom)))
	//{
	//	return false;
	//}
	//if (FAILED(CreateResource()))
	//{
	//	return false;
	//}	

	return true;
}


bool GProjMain::Frame()
{
	m_pMainCamera->Frame();

	//m_CustomMap.Frame();
	m_HeightMap.Frame();
	g_pImmediateContext->UpdateSubresource(
		m_HeightMap.m_dxobj.g_pVertexBuffer.Get(), 0, 0, &m_HeightMap.m_VertexList.at(0), 0, 0);



	return true;
}
bool GProjMain::Render()
{
	//m_CustomMap.SetMatrix(m_pMainCamera->GetWorldMatrix(), m_pMainCamera->GetViewMatrix(),
	//	m_pMainCamera->GetProjMatrix());
	//m_CustomMap.Render(m_pImmediateContext);

	m_HeightMap.SetMatrix(m_pMainCamera->GetWorldMatrix(), m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	m_HeightMap.Render(m_pImmediateContext);
	
	return true;
}
bool GProjMain::Release()
{
	//m_CustomMap.Release();
	m_HeightMap.Release();
	SAFE_ZERO(m_pMainCamera);

	
	return true;
}

HRESULT GProjMain::CreateResource()
{
	HRESULT hr;
	
	return S_OK;
}
HRESULT GProjMain::DeleteResource()
{
	HRESULT hr = S_OK;
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	return S_OK;
}

GProjMain::GProjMain(void)
{
	m_pMainCamera = NULL;
	

}
GProjMain::~GProjMain(void){
	
}



int GProjMain::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	return -1;
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	GProjMain gProjMain; g_pMain = &gProjMain;
	if (!gProjMain.InitWindow(hInstance, nCmdShow, L"GRustum Test", 1024, 768)) { return 0; }
	ShowCursor(TRUE);
	gProjMain.Run();	return 1;
}


