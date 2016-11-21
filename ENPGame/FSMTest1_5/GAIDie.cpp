#include "_stdafx.h"

GAIDie * GAIDie::pInstance_ = 0;

bool GAIDie::Init()
{

	return true;
}
bool GAIDie::Frame()
{
  // die 애니메이션 연출
	
	return true;
}
bool GAIDie::Render()
{

	return true;
}
bool GAIDie::Release()
{
	return true;
}
HRESULT GAIDie::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIDie::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIDie::GAIDie()
{
	pInstance_ = 0;
}


GAIDie::~GAIDie()
{
}
int GAIDie::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainCamera != nullptr)
	{
		m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	}
	return -1;
}

