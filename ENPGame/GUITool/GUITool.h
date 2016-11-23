
// GUITool.h : GUITool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.
#include "GCoreLibV2.h"
//#include "GHeroObj.h"
#include  "GZombie.h"

#define G_MACRO_MODELVIEW 1

//#define G_MACRO_MODELROT 1

#ifdef G_MACRO_MODELVIEW
//#include "GModelViewCamera.h"
#include "GModelCamera.h"
#else
#include "GCamera.h"
#endif

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GCharCore32d.lib" )	
#else
#pragma comment( lib, "GCharCore32.lib" )
#endif

// CAIToolApp:
// �� Ŭ������ ������ ���ؼ��� GUITool.cpp�� �����Ͻʽÿ�.
//

enum G_CHAR_TOOL_EXT {
	G_TOOL_EXT_GUI,
	G_TOOL_EXT_GBS,
	G_TOOL_EXT_CNT
};



class CGUIToolApp : public CWinAppEx, public GCoreLibV2
{
public:
	G_CHAR_TOOL_EXT m_FileExt;
	vector<CString> m_vecStr;


	D3DXMATRIX  m_matWorld;


	T_STR_VECTOR m_LoadFiles;
	bool		Load();
	bool		LoadFileDlg(TCHAR* szExt, TCHAR* szTitle);

	HRESULT CreateResource();
	HRESULT DeleteResource();
public:
	CGUIToolApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
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

extern CGUIToolApp theApp;
