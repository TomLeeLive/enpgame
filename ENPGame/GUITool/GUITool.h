
// GUITool.h : GUITool 응용 프로그램에 대한 주 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.
#include "GCoreLibV2.h"

//추가함 for UI [start]
#include "GDxHelperEx.h"
#include "GPlaneRect.h"
using namespace DX;
//추가함 for UI [end]

#include "GCamera.h"

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GCharCore32d.lib" )	
#else
#pragma comment( lib, "GCharCore32.lib" )
#endif

// CAIToolApp:
// 이 클래스의 구현에 대해서는 GUITool.cpp을 참조하십시오.
//

enum G_CHAR_TOOL_EXT {
	G_TOOL_EXT_GUI,
	G_TOOL_EXT_GBS,
	G_TOOL_EXT_CNT
};



class CGUIToolApp : public CWinAppEx, public GCoreLibV2
{
public:
	//추가함 for UI [start]
	VS_CONSTANT_BUFFER			m_cbData;
	std::vector<GControlUI*>	m_pUIList;
	GControlUI*					m_pSelectPlane;
	ComPtr<ID3D11ShaderResourceView> m_pTextureSRV[3];
	GSceneUI						m_Scene;
	GControlUI* AddRect(GUI_TYPE type);
	GControlUI* SelectRect();
	//추가함 for UI [end]

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

extern CGUIToolApp theApp;
