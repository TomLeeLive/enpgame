
// GUITool.h : GUITool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


//�߰��� for UI [start]
#include "_stdafx.h"
//�߰��� for UI [end]

#include "GCamera.h"


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
	//�߰��� for UI [start]
	GUIMaker    m_UIManager;
	//�߰��� for UI [end]

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
	afx_msg void OnGuiLoad();
	afx_msg void OnGuiSave();
};

extern CGUIToolApp theApp;
