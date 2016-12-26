#pragma once

#define G_MACRO_TESTCODE_ADD 1


class GAIZombieMgr
{
public:

#ifdef G_MACRO_TESTCODE_ADD
	list<shared_ptr<GNewZombie>> m_Zomb;
#else
	vector<shared_ptr<GNewZombie>> m_Zomb;
#endif
	
	bool Load(int iNum);


public:
	bool		Init(int iNum);
	bool		Frame(D3DXMATRIX matHeroWorld, D3DXMATRIX matHeroWorld2);
	bool		Render(GCamera* camera);
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

