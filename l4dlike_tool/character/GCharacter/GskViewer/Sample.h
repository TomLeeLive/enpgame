#pragma once
#include "GBasisLib_0.h"
#include "GObject.h"
#include "GModelViewCamera.h"
class Sample : public GBasisLib_0
{
public:
	GObject		m_GObject;	
	shared_ptr<GModelViewCamera > m_pMainCamera;
	D3DXMATRIX  m_matWorld;
public:	
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();	
	//--------------------------------------------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();	
	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	//--------------------------------------------------------------------------------------
	// 파일 선택하여 로드( 단축기 : O )
	//--------------------------------------------------------------------------------------
	T_STR_VECTOR m_LoadFiles; 
	bool		Load();
	bool		LoadFileDlg( TCHAR* szExt, TCHAR* szTitle );
public:
	Sample(void);
	virtual ~Sample(void);
};
