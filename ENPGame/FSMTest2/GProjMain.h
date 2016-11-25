#pragma once




class GProjMain : public GCoreLibV2
{
public:
	void ChangeZombState(int iNum, G_AI state);
	void ChangeZombState(int iNum, TCHAR* str);


	int iChange;
	shared_ptr<GCamera > m_pMainCamera;
	D3DXMATRIX  m_matBoxWorld;
	//D3DXMATRIX  m_matWorld1;

	D3DXMATRIX  m_temp;





	//vector<shared_ptr<GNewZombieMgr>>m_CharNZomb;


	GShape*	m_Box;
	//GNewZombie* m_Zomb[G_DEFINE_MAX_AI_ZOMBIE];
	vector<shared_ptr<GNewZombie>> m_Zomb;
	bool Load();

public:

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