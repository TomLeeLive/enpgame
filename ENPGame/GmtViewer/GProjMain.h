#pragma once
#include "GCoreLibV2.h"
#include "GObject.h"
#include "GModelViewCamera.h"

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GCharCore32d.lib" )
#else
#pragma comment( lib, "GCharCore32.lib" )
#endif

class GProjMain : public GCoreLibV2
{
public:
	GBoneObj		m_tObject;
	shared_ptr<GModelViewCamera > m_pMainCamera;
	D3DXMATRIX  m_matWorld;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	int		WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//--------------------------------------------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();	
public:
	//--------------------------------------------------------------------------------------
	// ���� �����Ͽ� �ε�( ����� : O )
	//--------------------------------------------------------------------------------------
	T_STR_VECTOR m_LoadFiles; 
	bool		Load();
	bool		LoadFileDlg( TCHAR* szExt, TCHAR* szTitle );
public:
	GProjMain(void);
	virtual ~GProjMain(void);
};

extern GProjMain*	g_pMain; //�ܺ� ���� ���� ����
