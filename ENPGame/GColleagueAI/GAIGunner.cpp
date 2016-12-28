#include "Col_stdafx.h"

//GAIDie * GAIDie::pInstance_ = 0;

bool GAIGunner::Init()
{
	return true;
}
bool GAIGunner::Frame()
{

	return true;
}
bool GAIGunner::Render()
{

	return true;
}
bool GAIGunner::Release()
{
	return true;
}
HRESULT GAIGunner::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIGunner::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIGunner::GAIGunner()
{
	GAIColleagueSeq::InitGSeq();
}


GAIGunner::~GAIGunner()
{
}
int GAIGunner::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//if (m_pMainCamera != nullptr)
	//{
	//	m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	//}
	return -1;
}

