#pragma once
#include"GNewZombie.h"
enum ZombieNum {
	ZombieNum = 5
};
class GAIMove : public GSeq
{
public:
	static GSeq* CreateInstance() {
		if (pInstance_ == 0) pInstance_ = new GAIMove;
		return pInstance_;
	}
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	GNewZombie* m_Zombie;
	int hp;
	D3DXVECTOR3 m_Z_Look[ZombieNum];
	D3DXMATRIX m_Z_Trans[ZombieNum];
	void		RendomMove();
	float ZombieDistance[ZombieNum];
	//----------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
	
	D3DXVECTOR3 m_RandomPoint[ZombieNum];
	D3DXVECTOR3 m_RandomDestination[ZombieNum];
	D3DXMATRIX  m_RandomRotation[ZombieNum];
	D3DXVECTOR3 vZombiePosition[ZombieNum];
	D3DXVECTOR3 vBoxPosition[ZombieNum];
	D3DXVECTOR3 vRDestLook1[ZombieNum];
	D3DXVECTOR3 vRDestLook[ZombieNum];
	D3DXVECTOR3 vZRight[ZombieNum];
	D3DXVECTOR3 vZUp[ZombieNum];
	D3DXVECTOR3 vDistance[ZombieNum];

	GTimer * TIme;
	float fTime = 15.0f;
	float m_fSecondPerFrmae = 0.0f;
	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return -1; };
public:
	virtual ~GAIMove();
protected:
	GAIMove();
private:
	static GAIMove *pInstance_;
};

