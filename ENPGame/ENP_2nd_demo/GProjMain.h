#pragma once

enum G_SEQ {
	G_SEQ_END = 0,
	G_SEQ_OVER = 1,
	G_SEQ_HOWTO =2,
	G_SEQ_INTRO =3,
	G_SEQ_MENU = 4,
	G_SEQ_SINGLE = 5,
	G_SEQ_SURVIVAL = 6,
	G_SEQ_CNT
};



class GProjMain : public GCoreLibV2
{
public:

	GSeq * m_pGameSeq[G_SEQ_CNT];
	GSeq * m_pCurrentSeq;

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
	GProjMain(void);
	virtual ~GProjMain(void);
};

extern GProjMain*	g_pMain; //�ܺ� ���� ���� ����