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
	D3DXMATRIX  m_matWorld;

	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool ZombieAttack(int i, D3DXVECTOR3 look, D3DXVECTOR3 Right, D3DXVECTOR3 Up);
	GNewZombieMgr * ZombieMgr;
	int	WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	int hp;
	D3DXVECTOR3 A_Look;
	D3DXMATRIX A_Trans[ZombieNum];
	float ZombieDistance[ZombieNum];
	

	D3DXVECTOR3 RandomPoint;
	D3DXMATRIX m_ABoxRotation;
	D3DXVECTOR3 vZombiePosition[ZombieNum];
	D3DXVECTOR3 vBoxPosition[ZombieNum];
	D3DXVECTOR3 vADestLook1[ZombieNum];
	D3DXVECTOR3 vADestLook[ZombieNum];
	D3DXVECTOR3 vARight[ZombieNum];
	D3DXVECTOR3 vAUp[ZombieNum];
	D3DXVECTOR3 vDistance[ZombieNum];

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


