#pragma once


//class GAIZombieMgr;

class GProjMain : public GCoreLibV2
{
public:


	GAIZombieMgr		m_GAIZombMgr;
	//int iChange;
	shared_ptr<GCamera > m_pMainCamera;
	D3DXMATRIX  m_matBoxWorld;
	//D3DXMATRIX  m_matWorld1;

	//D3DXMATRIX  m_temp;





	//vector<shared_ptr<GNewZombieMgr>>m_CharNZomb;


	GShape*	m_Box;
	//GNewZombie* m_Zomb[G_DEFINE_MAX_AI_ZOMBIE];



public:

	//float m_fSecondPerFrmae;

public:
//	static GProjMain* CreateInstance() { return 0; }
 bool		Init();
 bool		Frame();
 bool		Render();
 bool		Release();
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