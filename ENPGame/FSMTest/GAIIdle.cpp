#include "_stdafx.h"

GAIIdle * GAIIdle::pInstance_ = 0;

bool GAIIdle::Init()
{
	return true;
}
bool GAIIdle::Frame()
{

	TimeCount += g_fSecPerFrame;

	if (TimeCount >5.0f)
		
		g_pMain->m_pCurrentSeq = g_pMain->m_GameSeq[G_AI_MOVE];
	return true;
}
bool GAIIdle::Render()
{

	return true;
}
bool GAIIdle::Release()
{
	return true;
}
HRESULT GAIIdle::CreateResource()
{
	HRESULT hr;

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

