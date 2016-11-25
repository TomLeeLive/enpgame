#pragma once
#include"GNewZombieMgr.h"
enum ZombieNum {
	ZombieNum = G_DEFINE_MAX_AI_ZOMBIE
};
class GAIMove : public GAISeq
{
public:
	static GAISeq* CreateInstance() {
		if (pInstance_ == 0) pInstance_ = new GAIMove;
		return pInstance_;
	}
	bool Init(int iMyIndex);
	bool Frame(int iMyIndex);
	bool Render();
	bool Release();

public:
	int hp;
	bool ZombieMove(int i, D3DXVECTOR3 look, D3DXVECTOR3 Right, D3DXVECTOR3 Up);
	//----------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();

	//GNewZombieMgr * ZombieMgr;

	D3DXMATRIX Trans;
	D3DXMATRIX Rotation;
	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return -1; };
public:
	virtual ~GAIMove();
protected:
	GAIMove();
private:
	static GAIMove *pInstance_;
};

