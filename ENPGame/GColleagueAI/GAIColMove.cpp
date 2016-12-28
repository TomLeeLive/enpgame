#include "Col_stdafx.h"

bool GAIColMove::Init()
{

	return true;
}

bool GAIColMove::Frame()
{

	return true;
}
bool GAIColMove::Render()
{

	return true;
}
bool GAIColMove::Release()
{
	return true;
}
HRESULT GAIColMove::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIColMove::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIColMove::GAIColMove()
{


	GAIColleagueSeq::InitGSeq();


}


GAIColMove::~GAIColMove()
{
}
int GAIColMove::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//if (m_pMainCamera != nullptr)
	//{
	//	m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	//}
	return -1;
}

