
// GciCharTool.h : GciCharTool 응용 프로그램에 대한 주 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.
#include "GCoreLibV2.h"
#include "GHeroObj.h"
#include "GCamera.h"

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GCharCore32d.lib" )	
#else
#pragma comment( lib, "GCharCore32.lib" )
#endif

// CAIToolApp:
// 이 클래스의 구현에 대해서는 GciCharTool.cpp을 참조하십시오.
//

class CGciCharToolApp : public CWinAppEx, public GCoreLibV2
{
public:
	shared_ptr<GCamera > m_pMainCamera;
	D3DXMATRIX  m_matWorld;
	vector<shared_ptr<GHeroObj>>	m_HeroObj;

	T_STR_VECTOR m_LoadFiles;
	bool		Load();
	bool		LoadFileDlg(TCHAR* szExt, TCHAR* szTitle);

public:
	CGciCharToolApp();


// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 구현입니다.
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

public:
	virtual bool Frame();
	virtual bool Render();

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
	afx_msg void OnCharload();
	afx_msg void OnCharsave();
};

extern CGciCharToolApp theApp;
