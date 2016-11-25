#pragma once

class GAIAttack : public GSeq
{
private:
	static GAIAttack *pInstance_;
public:
	static GSeq* CreateInstance()
	{
		if (pInstance_ == 0) pInstance_ = new GAIAttack;
		return pInstance_;
	}
	shared_ptr<GCamera > m_pMainCamera;

	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool ZombieAttack(int i, D3DXVECTOR3 look, D3DXVECTOR3 Right, D3DXVECTOR3 Up);
	int	WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	int hp;

	GNewZombieMgr * ZombieMgr;

	D3DXMATRIX Trans[ZombieNum];
	D3DXMATRIX Rotation[ZombieNum];
	//----------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
public:
	virtual ~GAIAttack();
protected:
	GAIAttack();
};


