#include "Col_stdafx.h"

//GAIDie * GAIDie::pInstance_ = 0;

bool GAIHealer::Init()
{
	return true;
}
bool GAIHealer::Frame()
{

	return true;
}
bool GAIHealer::Render()
{

	return true;
}
bool GAIHealer::Release()
{
	return true;
}
HRESULT GAIHealer::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIHealer::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIHealer::GAIHealer()
{
	GAIColleagueSeq::InitGSeq();
}


GAIHealer::~GAIHealer()
{
}
int GAIHealer::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//if (m_pMainCamera != nullptr)
	//{
	//	m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	//}
	return -1;
}

