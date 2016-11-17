#pragma once

enum G_AI {
	G_AI_IDLE = 0,
	G_AI_MOVE,
	G_AI_ATTACK,
	G_AI_DIE,
	G_AI_FOLLOW,
	G_AI_CNT
};
//enum G_ZOMBIE_STATE {
//	G_ZOMB_IDLE = 0,
//	G_ZOMB_WALK,
//	G_ZOMB_ATTACK,
//	G_ZOMB_DIE,
//	G_ZOMB_FOLLOW,
//	G_ZOMB_CNT
//};


class GProjMain : public GCoreLibV2
{
public:
	void ChangeZombState(int iNum, G_ZOMB_ST state);
	void ChangeZombState(int iNum, TCHAR* str);

	int iChange;
	shared_ptr<GCamera > m_pMainCamera;
	D3DXMATRIX  m_matBoxWorld;
	D3DXMATRIX  m_matWorld1;
	D3DXMATRIX  m_RandomRotation[5];
	D3DXMATRIX  m_BoxRotation[5];
	D3DXMATRIX  m_RandomRotResult[5];
	D3DXMATRIX  m_BoxRotResult[5];
	D3DXMATRIX  m_temp;


	vector<shared_ptr<GNewZombie>>m_CharNZomb;

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