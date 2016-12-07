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
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();

public:
	GAIZombieMgr();
	virtual ~GAIZombieMgr();
};

