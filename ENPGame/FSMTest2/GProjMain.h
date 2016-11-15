#pragma once

enum G_AI {
	G_AI_IDLE = 0,
	G_AI_MOVE = 1,
	G_AI_ATTACK =2,
	G_AI_DIE =3,
	G_AI_CNT
};
enum G_ZOMBIE_STATE {
	G_ZOMB_IDLE = 0,
	G_ZOMB_ATTACK,
	G_ZOMB_WALK,
	G_ZOMB_DIE,
	G_ZOMB_CNT
};


class GProjMain : public GCoreLibV2
{
public:
	int iChange;
	shared_ptr<GCamera > m_pMainCamera;
	D3DXMATRIX  m_matWorld;
	D3DXMATRIX  m_matWorld1;
	D3DXMATRIX  m_Rotation;
	D3DXMATRIX  m_matZombieWorld;
	D3DXMATRIX  m_Result;
	D3DXMATRIX  m_temp;


	vector<shared_ptr<GZombie>>m_HeroObj;

	GShape*		m_Box;
	GShape*		m_Box1;
	bool m_bDead = true;
	bool Load();

public:
	GSeq * m_GameSeq[G_AI_CNT];
	GSeq * m_pCurrentSeq;
	float m_fSecondPerFrmae;

public:
	static GProjMain* CreateInstance() { return 0; }
 bool		Init();
 bool		Frame();
 bool		Render();
 bool		Release();
 int		WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//----------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
 HRESULT		CreateResource();
 HRESULT		DeleteResource();

public:
	GProjMain(void);
	virtual ~GProjMain(void);
};
extern GProjMain*   g_pMain;