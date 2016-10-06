#pragma once
#include "GBasisLib_0.h"
#include "GObject.h"
#include "GModelViewCamera.h"
class Sample : public GBasisLib_0
{
public:
	GObject		m_GObject;	
	shared_ptr<GModelViewCamera > m_pMainCamera;
	D3DXMATRIX  m_matWorld;
public:	
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();	
	//--------------------------------------------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();	
	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	//--------------------------------------------------------------------------------------
	// ���� �����Ͽ� �ε�( ����� : O )
	//--------------------------------------------------------------------------------------
	T_STR_VECTOR m_LoadFiles; 
	bool		Load();
	bool		LoadFileDlg( TCHAR* szExt, TCHAR* szTitle );
public:
	Sample(void);
	virtual ~Sample(void);
};
