#include "Sample.h"



Sample::Sample()
{
}


Sample::~Sample()
{
}
GBASIS_RUN(L"GMapSample_0");

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	Sample gSample;
	if (!gSample.InitWindow(hInstance, nCmdShow, L"GMapSample_0"))
	{
		return 0;
	}
	ShowCursor(TRUE);
	gSample.Run();	
	return 1;
}