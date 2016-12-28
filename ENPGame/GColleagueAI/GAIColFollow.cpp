#include "Col_stdafx.h"

bool GAIColFollow::Init()
{

	return true;
}

bool GAIColFollow::Frame()
{

	return true;
}
bool GAIColFollow::Render()
{

	return true;
}
bool GAIColFollow::Release()
{
	return true;
}
HRESULT GAIColFollow::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIColFollow::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIColFollow::GAIColFollow()
{


	GAIColleagueSeq::InitGSeq();


}


GAIColFollow::~GAIColFollow()
{
}
int GAIColFollow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//if (m_pMainCamera != nullptr)
	//{
	//	m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	//}
	return -1;
}

