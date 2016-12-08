#pragma once
#include "GCoreLibV2.h"
#include "GZombie.h"
#include "GHero.h"


//������Ʈ ��ġ
#define G_OBJ_LOC_GUN_SHOTGUN _T("data/object/shotgun/shotgun.GBS")
//������Ʈ �Ŵ��� ��� �̸�
#define G_OBJ_NAME_GUN_SHOTGUN L"shotgun.GBS"



//#define G_MACRO_MODELVIEW 1

#ifdef G_MACRO_MODELVIEW
#include "GModelViewCamera.h"
#else
#include "GCamera.h"
#endif

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GCharCore32d.lib" )	
#else
#pragma comment( lib, "GCharCore32.lib" )
#endif

class GProjMain : public GCoreLibV2
{
#ifdef G_MACRO_MODELVIEW
	shared_ptr<GModelViewCamera > m_pMainCamera;
#else
	shared_ptr<GCamera > m_pMainCamera;
#endif
	/*
	GModel*		m_ObjGun;
	D3DXMATRIX	m_matObjGunWld, m_matObjGunScl, m_matObjGunRot, m_matObjGunTrans;
	*/
	D3DXMATRIX  m_matWorld;
	vector<shared_ptr<GHero>>	m_HeroObj;
public:	
	bool		Init();
	bool		Frame();
	bool		Render();	
	bool		Release();
	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//----------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
public:
	//--------------------------------------------------------------------------------------
	// ���� �����Ͽ� �ε�( ����� : O )
	//--------------------------------------------------------------------------------------
	bool		Load();
public:
	GProjMain(void);
	virtual ~GProjMain(void);
};

extern GProjMain*	g_pMain; //�ܺ� ���� ���� ����

