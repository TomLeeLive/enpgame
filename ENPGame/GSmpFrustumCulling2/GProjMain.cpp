#include "_stdafx.h"

GProjMain* g_pMain;

#define NUM_OBJECTS 100


bool GProjMain::Init()
{
	HRESULT hr;
	//카메라 생성
	SAFE_NEW(m_pMainCamera, GCamera);

	D3DXVECTOR3 vTargetPosition = D3DXVECTOR3(0.0f, -0.1f, 0.0f);
	D3DXVECTOR3 vUpVector(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 vCameraPosition = D3DXVECTOR3(0.0f, 1.0f, -0.1f);
	// 메인 카메라 뷰 행렬 세팅
	m_pMainCamera->SetViewMatrix(vCameraPosition, vTargetPosition, vUpVector);

	m_pMainCamera->SetProjMatrix(D3DX_PI * 0.25f,
		m_SwapChainDesc.BufferDesc.Width / (float)(m_SwapChainDesc.BufferDesc.Height),
		0.1f, 10000.0f);


	//CustomizeMap
	TMapDesc MapDesc = { 50, 50, 1.0f, 0.1f,L"data/baseColor.jpg", L"data/shader/CustomizeMap.hlsl" };
	m_CustomMap.Init(GetDevice(), m_pImmediateContext);
	if (FAILED(m_CustomMap.Load(MapDesc)))
	{
		return false;
	}
	if (FAILED(CreateResource()))
	{
		return false;
	}

	//obj
	int iIndex = -1;
	iIndex = I_ObjMgr.Load(g_pd3dDevice, G_OBJ_LOC_LAB, G_SHA_BOX);				if (iIndex < 0) return false;	
	
	for (int i = 0; i < G_OBJ_CNT; i++) {
		D3DXMatrixIdentity(&m_matObjWld[i]);
		D3DXMatrixIdentity(&m_matObjScl[i]);
		D3DXMatrixIdentity(&m_matObjRot[i]);
		D3DXMatrixIdentity(&m_matObjTrans[i]);
	}

	m_Obj[G_OBJ_LAB] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB], 2, 2, 2);
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB], 1000.0f, 0.0f, 1000.0f);
	m_matObjWld[G_OBJ_LAB] = m_matObjScl[G_OBJ_LAB] * m_matObjRot[G_OBJ_LAB] * m_matObjTrans[G_OBJ_LAB];


	return true;
}


bool GProjMain::Frame()
{
	m_pMainCamera->Frame();

	m_CustomMap.Frame();
	g_pImmediateContext->UpdateSubresource(
		m_CustomMap.m_dxobj.g_pVertexBuffer.Get(), 0, 0, &m_CustomMap.m_VertexList.at(0), 0, 0);

	for (int i = 0; i < G_OBJ_CNT; i++) 
	{
		m_Obj[i]->Frame();
	}

	return true;
}
bool GProjMain::Render()
{
	m_CustomMap.SetMatrix(m_pMainCamera->GetWorldMatrix(), m_pMainCamera->GetViewMatrix(),
		m_pMainCamera->GetProjMatrix());
	m_CustomMap.Render(m_pImmediateContext);

	for (int i = 0; i < G_OBJ_CNT; i++) 
	{
		m_Obj[i]->SetMatrix(&m_matObjWld[i], m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
		m_Obj[i]->Render(g_pImmediateContext);
	}

	return true;
}
bool GProjMain::Release()
{
	m_CustomMap.Release();
	SAFE_ZERO(m_pMainCamera);

	I_ObjMgr.Release();

	return true;
}

HRESULT GProjMain::CreateResource()
{
	HRESULT hr;
	{
		float fAspectRatio = m_SwapChainDesc.BufferDesc.Width /
			(float)m_SwapChainDesc.BufferDesc.Height;
		//m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 500.0f);


	}

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
GProjMain::~GProjMain(void)
{

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


