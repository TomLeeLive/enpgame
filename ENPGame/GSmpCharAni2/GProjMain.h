#pragma once
#include "GCoreLibV2.h"
#include "GZombie.h"

enum G_ZOMBIE_STATE {
	G_ZOMB_IDLE = 0,
	G_ZOMB_ATTACK,
	G_ZOMB_WALK,
	G_ZOMB_DIE,
	G_ZOMB_CNT
};
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
	GCharacter* pChar0[G_ZOMB_CNT];
	D3DXMATRIX  m_matWorld;
	vector<shared_ptr<GZombie>>	m_HeroObj;
	GCharacter m_ZombieAni[G_ZOMB_CNT];
public:	
	bool		Init();
	bool		Frame();
	bool		Render();	
	bool		Release();
	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//----------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
public:
	//--------------------------------------------------------------------------------------
	// 파일 선택하여 로드( 단축기 : O )
	//--------------------------------------------------------------------------------------
	bool		Load();
public:
	GProjMain(void);
	virtual ~GProjMain(void);
};

extern GProjMain*	g_pMain; //외부 연결 범위 선언

