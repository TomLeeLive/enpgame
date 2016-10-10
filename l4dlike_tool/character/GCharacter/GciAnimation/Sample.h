#pragma once
#include "GBasisLib_0.h"
#include "GHeroObj.h"
#include "GCamera.h"


class Sample : public GBasisLib_0
{
	shared_ptr<GCamera > m_pMainCamera;
	D3DXMATRIX  m_matWorld;
	vector<shared_ptr<GHeroObj>>	m_HeroObj;
public:	
	bool		Init();
	bool		Frame();
	bool		Render();	
	bool		Release();
	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//----------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
public:
	//--------------------------------------------------------------------------------------
	// 파일 선택하여 로드( 단축기 : O )
	//--------------------------------------------------------------------------------------
	T_STR_VECTOR m_LoadFiles;
	bool		Load();
	bool		LoadFileDlg(TCHAR* szExt, TCHAR* szTitle);
public:
	Sample(void);
	virtual ~Sample(void);
};
