#pragma once
//#include"GNewZombieMgr.h"
class GAIColMove : public GAIColSeq
{
public:
	float		m_fTime;// = 0.0f;
	D3DXVECTOR3 m_vPos;

	static D3DXVECTOR3 RandomMove();

	bool Init(GAICol* iMyIndex);
	bool Frame(GAICol* iMyIndex,D3DXMATRIX matHeroWorld, D3DXMATRIX matHeroWorld2);
	bool Render();
	bool Release();
	//----------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();


	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return -1; };
public:
	virtual ~GAIColMove();
	GAIColMove();
protected:

};

