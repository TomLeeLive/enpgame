#include "Col_stdafx.h"

bool GAIColAttack::Init()
{

	return true;
}

bool GAIColAttack::Frame()
{

	return true;
}
bool GAIColAttack::Render()
{

	return true;
}
bool GAIColAttack::Release()
{
	return true;
}
HRESULT GAIColAttack::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIColAttack::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIColAttack::GAIColAttack()
{


	GAIColleagueSeq::InitGSeq();


}


GAIColAttack::~GAIColAttack()
{
}
int GAIColAttack::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//if (m_pMainCamera != nullptr)
	//{
	//	m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	//}
	return -1;
}

