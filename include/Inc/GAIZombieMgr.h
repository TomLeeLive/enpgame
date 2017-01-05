#pragma once

class GAIZombieMgr
{
public:
	list<shared_ptr<GNewZombie>> m_Zomb;
	bool Load(int iNum, D3DXVECTOR3 position);


public:
	bool		Init(int iNum);
	bool		Frame(D3DXMATRIX matHeroWorld, D3DXMATRIX matHeroWorld2);
	bool		Render(GCamera* camera);
	bool		Render(D3DXMATRIX matView, D3DXMATRIX matProj);
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

