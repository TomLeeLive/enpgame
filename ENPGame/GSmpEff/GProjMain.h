#pragma once


class GProjMain : public GCoreLibV2
{
public:
	GCamera*	m_pMainCamera;
	EffManager	m_EffManager;
public:	
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	//--------------------------------------------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();	

public:
	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	GProjMain(void);
	virtual ~GProjMain(void);
};

extern GProjMain*	g_pMain; //�ܺ� ���� ���� ����