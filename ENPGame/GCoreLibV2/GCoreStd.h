#ifndef GCORESTD_H
#define GCORESTD_H
#include "GUtils.h"
#include "GDxHelper.h"

#pragma comment( lib, "winmm.lib" )

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GCoreLib32d.lib" )
#else
#pragma comment( lib, "GCoreLib32.lib" )
#endif
namespace GCORESTD
{
	extern float		g_fSecPerFrame;
	extern float		g_fDurationTime;
	extern HWND			g_hWnd;
	extern HINSTANCE	g_hInstance;
	extern UINT			g_iClientWidth;
	extern UINT			g_iClientHeight;
}
using namespace GCORESTD;
//////////////////////////////////////////////
// WinMain ∏≈≈©∑Œ
//////////////////////////////////////////////
#define GCORE_START int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ){ GProjMain gProjMain;
#define GCORE_WIN(x) if( !gProjMain.InitWindow( hInstance, nCmdShow,  L#x ) )	{	return 0;	}	ShowCursor ( TRUE );gProjMain.Run();	return 1; }
#define GCORE_RUN(x) GCORE_START; GCORE_WIN(x);

#endif //GCORESTD_H