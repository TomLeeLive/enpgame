#pragma once
class GAIZombieMgr
{
public:


	vector<shared_ptr<GNewZombie>> m_Zomb;
	bool Load();


public:
	bool		Init();
	bool		Frame();
	bool		Render(GCamera* camera);
	bool		Release();
	int		WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


	//----------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();

public:
	GAIZombieMgr();
	virtual ~GAIZombieMgr();
};

