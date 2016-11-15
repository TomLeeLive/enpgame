#pragma once

enum G_AI {
	G_AI_IDLE = 0,
	G_AI_MOVE = 1,
	G_AI_ATTACK =2,
	G_AI_DIE =3,
	G_AI_CNT
};
class GProjMain : public GCoreLibV2
{
public:
	shared_ptr<GCamera > m_pMainCamera;
	D3DXMATRIX  m_matWorld;
	D3DXMATRIX  m_matWorld1;
	D3DXMATRIX  m_Rotation;
	D3DXMATRIX  m_Result;
	D3DXMATRIX  m_temp;

	GShape*		m_Box;
	GShape*		m_Box1;
	bool m_bDead = true;


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
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//----------------------------------------------------
 HRESULT		CreateResource();
 HRESULT		DeleteResource();

public:
	GProjMain(void);
	virtual ~GProjMain(void);
};
extern GProjMain*   g_pMain;