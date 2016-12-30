
// MapTool.h : MapTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.
#include "GCoreLibV2.h"

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GMapCore32d.lib" )
#else
#pragma comment( lib, "GMapCore32.lib" )
#endif

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GCharCore32d.lib" )
#else
#pragma comment( lib, "GCharCore32.lib" )
#endif


//#include "map/GNoiseMap.h"
//#include "map/GQuadTreeIndex.h"
//#include "map/GMapObject.h"
#include "map/GMap.h"
#include "map/GQuadTree.h"
#include "GCamera.h"



#include "GCreateMapDlg.h"
#include "GSaveMapDlg.h"


#include "GMapMgr.h"
// CMapToolApp:
// �� Ŭ������ ������ ���ؼ��� MapTool.cpp�� �����Ͻʽÿ�.
//



class CMapToolApp : public CWinAppEx, public GCoreLibV2
{
public:
	GMapMgr					m_MapMgr;
	shared_ptr<GCamera >	m_pMainCamera;
	ComPtr<ID3D11PixelShader>   m_pPixelShader;// ���ν��� ���� �Ƚ����̴�

public:
	bool			Init();
	bool			Frame();
	bool			Render();
	bool			Release();
	

	//--------------------------------------------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//--------------------------------------------------------------------------------------
	HRESULT			CreateResource();
	HRESULT			DeleteResource();

	T_STR_VECTOR m_LoadFiles;
	bool  LoadFileDlg(TCHAR* szExt, TCHAR* szTitle);
	
public:
	CMapToolApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
};

extern CMapToolApp theApp;
