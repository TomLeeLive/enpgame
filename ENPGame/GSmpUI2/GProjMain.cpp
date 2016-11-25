#include "_stdafx.h"

GProjMain* g_pMain;

bool GProjMain::Init()
{
	m_UIManager.Init();
	return true;
}
bool GProjMain::Frame()
{
	m_UIManager.Frame(&m_SwapChainDesc);
	return true;
}
bool GProjMain::Render()
{
	D3DXMATRIX matTrans, matRotation, matZ;
	// 2초당 1회전( 1 초 * D3DX_PI = 3.14 )
	float t = m_Timer.GetElapsedTime() * D3DX_PI;

	m_UIManager.Render();

	return true;
}
bool GProjMain::Release()
{
	m_UIManager.Release();

	return true;
}

//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GProjMain::CreateResource()
{
	HRESULT hr;

	m_UIManager.CreateResource(&m_SwapChainDesc);

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
GCORE_RUN(L"GBasisSample UI_0");