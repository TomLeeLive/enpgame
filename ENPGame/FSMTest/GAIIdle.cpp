#include "_stdafx.h"

GAIIdle * GAIIdle::pInstance_ = 0;

bool GAIIdle::Init()
{
	return true;
}
bool GAIIdle::Frame()
{
	// 물체의 정지상태를 계산한다.
	float temp = (rand() * 7) % 50;
	g_pMain->m_matWorld1._41 = temp;
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

