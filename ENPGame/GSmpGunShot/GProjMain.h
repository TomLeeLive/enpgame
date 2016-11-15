#pragma once
#include "GCoreLibV2.h"
#include "GModelViewCamera.h"
#include "GObject.h"

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GCharCore32d.lib" )	
#else
#pragma comment( lib, "GCharCore32.lib" )
#endif

//속성:디버깅:명령->C:\Program Files\Autodesk\3ds Max 2016\3dsmax.exe
class GProjMain : public GCoreLibV2
{
public:
	GGbsObj		m_tbsobj;
	shared_ptr<GModelViewCamera >		m_pMainCamera;
	D3DXMATRIX m_matWorld;
public:	
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//--------------------------------------------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();	

public:
	GProjMain(void);
	virtual ~GProjMain(void);
};

extern GProjMain*	g_pMain; //외부 연결 범위 선언