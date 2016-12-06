
// KEffectTool.h : KEffectTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.
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
// �� Ŭ������ ������ ���ؼ��� KEffectTool.cpp�� �����Ͻʽÿ�.
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
// �����Դϴ�.
	afx_msg void OnAppAbout();
	virtual BOOL OnIdle(LONG iCount);
	DECLARE_MESSAGE_MAP()
};

extern CKEffectToolApp theApp;
