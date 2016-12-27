#pragma once

enum G_SEQ {
	G_SEQ_END = 0,
	G_SEQ_OVER,// = 1,
	G_SEQ_HOWTO,// =2,
	G_SEQ_INTRO,// =3,
	G_SEQ_MENU,// = 4,
	G_SEQ_SINGLE,// = 5,
	G_SEQ_SURVIVAL,// = 6,
	G_SEQ_LOADING,// =7,
	G_SEQ_CNT
};



class GProjMain : public GCoreLibV2
{
public:
	//GUIManager	m_UILoadingScreen;

	bool		ChangeSeq(G_SEQ seq);
	G_SEQ		GetCurSeq();
	GSeq*		m_pCurrentSeq;
//private:
	G_SEQ		m_CurSeq;				//���� ������ ��Ͽ�
	GSeq*		m_pGameSeq[G_SEQ_CNT];

public:	
	GSound		m_pSound;				// ����(fmod)
	bool		SoundLoad();
	void		ClipMouse(bool bClip);

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