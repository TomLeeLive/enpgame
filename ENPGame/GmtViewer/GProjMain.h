#pragma once
#include "GBasisLib_0.h"
#include "GObject.h"
#include "GModelViewCamera.h"
class GProjMain : public GBasisLib_0
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
