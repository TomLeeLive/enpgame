#include "_stdafx.h"

GProjMain* g_pMain;

#define NUM_OBJECTS 100


bool GProjMain::Init()
{
	HRESULT hr;
	SAFE_NEW(m_pCamera, GCamera);

	D3DXVECTOR3 vTargetPosition = D3DXVECTOR3(0.0f, -0.1f, 0.0f);
	D3DXVECTOR3 vUpVector(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 vCameraPosition = D3DXVECTOR3(0.0f, 1.0f, -0.1f);

	// 메인 카메라 뷰 행렬 세팅
	m_pCamera->SetViewMatrix(vCameraPosition,vTargetPosition,vUpVector);

	m_pCamera->SetProjMatrix(D3DX_PI * 0.25f,
		m_SwapChainDesc.BufferDesc.Width / (float)(m_SwapChainDesc.BufferDesc.Height),
		0.1f, 100.0f);

	return true;
}


bool GProjMain::Frame()
{
	m_pCamera->Frame();
	return true;
}
bool GProjMain::Render()
{	
	
	return true;
}
bool GProjMain::Release()
{
	SAFE_ZERO(m_pCamera);
	return true;
}

HRESULT GProjMain::CreateResource()
{
	HRESULT hr;
	{
		float fAspectRatio = m_SwapChainDesc.BufferDesc.Width /
			(float)m_SwapChainDesc.BufferDesc.Height;
		m_pCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 500.0f);
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

}
GProjMain::~GProjMain(void)
{

}



int GProjMain::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	return -1;
}
GCORE_RUN(GRustum Test);



