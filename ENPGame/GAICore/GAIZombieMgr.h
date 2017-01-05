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
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();

public:
	GAIZombieMgr();
	virtual ~GAIZombieMgr();
};

