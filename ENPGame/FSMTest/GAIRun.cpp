#include "_stdafx.h"

GAIRun * GAIRun::pInstance_ = 0;

bool GAIRun::Init()
{
	return true;
}
bool GAIRun::Frame()
{
	
	return true;
}
bool GAIRun::Render()
{

	return true;
}
bool GAIRun::Release()
{
	return true;
}
HRESULT GAIRun::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIRun::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIRun::GAIRun()
{
	pInstance_ = 0;
}


GAIRun::~GAIRun()
{
}
int GAIRun::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainCamera != nullptr)
	{
		m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	}
	return -1;
}

