#pragma once
class GAIFollow : public GSeq
{
private:
	static GAIFollow *pInstance_;
public:
	static GSeq* CreateInstance()
	{
		if (pInstance_ == 0) pInstance_ = new GAIFollow;
		return pInstance_;
	}
	shared_ptr<GCamera > m_pMainCamera;
	D3DXMATRIX  m_matWorld;

	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool ZombieFollow(int i, D3DXVECTOR3 look, D3DXVECTOR3 Right, D3DXVECTOR3 Up);
	int hp;
	GNewZombieMgr * ZombieMgr;

	D3DXVECTOR3 B_Look[ZombieNum];
	D3DXMATRIX B_Trans[ZombieNum];

	int	WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	D3DXMATRIX Trans[ZombieNum];
	D3DXMATRIX Rotation[ZombieNum];
	//----------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
public:
	virtual ~GAIFollow();
protected:
	GAIFollow();
};


