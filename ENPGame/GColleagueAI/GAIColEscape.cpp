#include "Col_stdafx.h"

bool GAIColEscape::Init()
{

	return true;
}

bool GAIColEscape::Frame()
{

	return true;
}
bool GAIColEscape::Render()
{

	return true;
}
bool GAIColEscape::Release()
{
	return true;
}
HRESULT GAIColEscape::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIColEscape::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIColEscape::GAIColEscape()
{


	GAIColleagueSeq::InitGSeq();


}


GAIColEscape::~GAIColEscape()
{
}
int GAIColEscape::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//if (m_pMainCamera != nullptr)
	//{
	//	m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	//}
	return -1;
}

