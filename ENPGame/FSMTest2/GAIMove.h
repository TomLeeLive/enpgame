#pragma once
#include"GNewZombieMgr.h"
enum ZombieNum {
	ZombieNum = G_DEFINE_MAX_AI_ZOMBIE
};
class GAIMove : public GAISeq
{
public:
	float		m_fTime;// = 0.0f;
	D3DXVECTOR3 m_vPos;

	static D3DXVECTOR3 RandomMove();

	bool Init(int iMyIndex);
	bool Frame(int iMyIndex);
	bool Render();
	bool Release();

public:
	int hp;
	//bool ZombieMove(int i, D3DXVECTOR3 look, D3DXVECTOR3 Right, D3DXVECTOR3 Up);
	//----------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();


	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return -1; };
public:
	virtual ~GAIMove();
	GAIMove();
protected:

};

