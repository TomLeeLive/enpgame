#include "Col_stdafx.h"

bool GAIColIDLE::Init()
{

	return true;
}

bool GAIColIDLE::Frame()
{

	return true;
}
bool GAIColIDLE::Render()
{

	return true;
}
bool GAIColIDLE::Release()
{
	return true;
}
HRESULT GAIColIDLE::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIColIDLE::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIColIDLE::GAIColIDLE()
{


	GAIColleagueSeq::InitGSeq();


}


GAIColIDLE::~GAIColIDLE()
{
}
int GAIColIDLE::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//if (m_pMainCamera != nullptr)
	//{
	//	m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	//}
	return -1;
}

