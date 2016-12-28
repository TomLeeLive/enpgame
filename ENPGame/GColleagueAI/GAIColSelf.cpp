#include "Col_stdafx.h"

bool GAIColSelf::Init()
{

	return true;
}

bool GAIColSelf::Frame()
{

	return true;
}
bool GAIColSelf::Render()
{

	return true;
}
bool GAIColSelf::Release()
{
	return true;
}
HRESULT GAIColSelf::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIColSelf::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIColSelf::GAIColSelf()
{


	GAIColleagueSeq::InitGSeq();


}


GAIColSelf::~GAIColSelf()
{
}
int GAIColSelf::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//if (m_pMainCamera != nullptr)
	//{
	//	m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	//}
	return -1;
}

