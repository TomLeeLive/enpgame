#pragma once
#include"GNewZombieMgr.h"
enum ZombieNum {
	ZombieNum = G_DEFINE_MAX_AI_ZOMBIE
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
	int hp;
	bool ZombieMove(int i, D3DXVECTOR3 look, D3DXVECTOR3 Right, D3DXVECTOR3 Up);
	//----------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();

	GNewZombieMgr * ZombieMgr;

	D3DXMATRIX Trans[ZombieNum];
	D3DXMATRIX Rotation[ZombieNum];
	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return -1; };
public:
	virtual ~GAIMove();
protected:
	GAIMove();
private:
	static GAIMove *pInstance_;
};

