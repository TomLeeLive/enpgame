#pragma once
#include "GCoreLibV2.h"
#include "GModelViewCamera.h"
#include "GObject.h"

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GCharCore32d.lib" )	
#else
#pragma comment( lib, "GCharCore32.lib" )
#endif

//�Ӽ�:�����:���->C:\Program Files\Autodesk\3ds Max 2016\3dsmax.exe
class GProjMain : public GCoreLibV2
{
public:
	GGbsObj		m_tbsobj;
	shared_ptr<GModelViewCamera >		m_pMainCamera;
	D3DXMATRIX m_matWorld;
public:	
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//--------------------------------------------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();	

public:
	GProjMain(void);
	virtual ~GProjMain(void);
};

extern GProjMain*	g_pMain; //�ܺ� ���� ���� ����