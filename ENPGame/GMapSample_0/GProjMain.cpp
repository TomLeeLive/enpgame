#include "GProjMain.h"



GProjMain::GProjMain()
{
}


GProjMain::~GProjMain()
{
}
//GCORE_RUN(L"GMapSample_0")
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	GProjMain gProjMain;
	if (!gProjMain.InitWindow(hInstance, nCmdShow, L"GMapSample_0"))
	{
		return 0;
	}
	ShowCursor(TRUE);
	gProjMain.Run();
	return 1;
}