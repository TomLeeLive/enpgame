#include "Col_stdafx.h"

bool GAIColHelp::Init()
{

	return true;
}

bool GAIColHelp::Frame()
{

	return true;
}
bool GAIColHelp::Render()
{

	return true;
}
bool GAIColHelp::Release()
{
	return true;
}
HRESULT GAIColHelp::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIColHelp::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIColHelp::GAIColHelp()
{


	GAIColleagueSeq::InitGSeq();


}


GAIColHelp::~GAIColHelp()
{
}
int GAIColHelp::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//if (m_pMainCamera != nullptr)
	//{
	//	m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	//}
	return -1;
}

