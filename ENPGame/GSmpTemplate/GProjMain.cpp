#include "_stdafx.h"

GProjMain* g_pMain;

bool GProjMain::Init()
{

	
	return true;
}

bool GProjMain::Render()
{	

	return true;
}
bool GProjMain::Release()
{


	return true;
}

bool GProjMain::Frame()
{	

	return true;
}

//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GProjMain::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GProjMain::DeleteResource()
{
	HRESULT hr = S_OK;

	return S_OK;
}
GProjMain::GProjMain(void)
{

}

GProjMain::~GProjMain(void)
{

}
int GProjMain::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	return -1;
}
GCORE_RUN(ENP Test);



