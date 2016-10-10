
// GciCharTool.h : GciCharTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.
#include "GBasisLib_0.h"
#include "GciAnimation/GHeroObj.h"
#include "GCamera.h"

// CAIToolApp:
// �� Ŭ������ ������ ���ؼ��� GciCharTool.cpp�� �����Ͻʽÿ�.
//

class CGciCharToolApp : public CWinAppEx, public GBasisLib_0
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
};

extern CGciCharToolApp theApp;
