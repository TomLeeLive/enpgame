
// GUITool.h : GUITool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.
#include "GCoreLibV2.h"

//�߰��� for UI [start]
#include "GDxHelperEx.h"
#include "GPlaneRect.h"
using namespace DX;
//�߰��� for UI [end]

#include "GCamera.h"

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
	//�߰��� for UI [start]
	VS_CONSTANT_BUFFER			m_cbData;
	std::vector<GControlUI*>	m_pUIList;
	GControlUI*					m_pSelectPlane;
	ComPtr<ID3D11ShaderResourceView> m_pTextureSRV[3];
	GSceneUI						m_Scene;
	GControlUI* AddRect(GUI_TYPE type);
	GControlUI* SelectRect();
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
	afx_msg void OnCharload();
	afx_msg void OnCharsave();
};

extern CGUIToolApp theApp;
