#pragma once


class GProjMain : public GCoreLibV2
{
public:
	GAIZombieMgr		m_GAIZombMgr;
	shared_ptr<GCamera > m_pMainCamera;

	D3DXMATRIX  m_matBoxWorld;
	D3DXMATRIX  m_matBoxWorld2;
	GShape*	m_Box;
	GShape*	m_Box2;
	
	bool SelectCharacter;
public:
 bool		Init();
 bool		Frame();
 bool		Render();
 bool		Release();
 bool		FollowTom(D3DXVECTOR3 vHeroTom, D3DXVECTOR3 vHeroJake);
 int		WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


	//----------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//----------------------------------------------------
 HRESULT		CreateResource();
 HRESULT		DeleteResource();

public:
	GProjMain(void);
	virtual ~GProjMain(void);
};
extern GProjMain*   g_pMain;