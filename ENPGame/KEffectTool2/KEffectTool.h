
// KEffectTool.h : KEffectTool 응용 프로그램에 대한 주 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.
#include "_stdafx.h"

#include "GCoreLibV2.h"
#include "GModelViewCamera.h"
#include "GUtils.h"



#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GEffectCore32d.lib" )
#else
#pragma comment( lib, "GEffectCore32.lib" )
#endif

// CKEffectToolApp:
// 이 클래스의 구현에 대해서는 KEffectTool.cpp을 참조하십시오.
//

class CKEffectToolApp : public CWinApp,public GCoreLibV2
{
public:
	EffManager m_EffMgr;

	CKEffectToolApp();
	shared_ptr<GCamera > m_pMainCamera;

	G_EFF_TOOL_EXT m_FileExt;
	T_STR_VECTOR m_LoadFiles;
	bool LoadFileDlg(TCHAR* szExt, TCHAR* szTitle);
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	HRESULT		CreateResource();
	HRESULT		DeleteResource();



	virtual BOOL InitInstance();
	virtual int ExitInstance();
// 구현입니다.
	afx_msg void OnAppAbout();
	virtual BOOL OnIdle(LONG iCount);
	DECLARE_MESSAGE_MAP()
};

extern CKEffectToolApp theApp;
