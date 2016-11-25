#pragma once

enum G_ZOMB_ST {
	G_ZOMB_ST_IDLE = 0,
	G_ZOMB_ST_WALK,
	G_ZOMB_ST_ATTACK,
	G_ZOMB_ST_DEAD,
	G_ZOMB_ST_FOLLOW,
	G_ZOMB_ST_CNT
};

enum G_AI {
	G_AI_IDLE = 0,
	G_AI_MOVE,
	G_AI_ATTACK,
	G_AI_DIE,
	G_AI_FOLLOW,
	G_AI_CNT
};

class GAISeq 
{
public:
	GCharacter*	 pChar0;
	D3DXMATRIX	 m_matWorld;
	D3DXMATRIX	 Trans;
	D3DXMATRIX	 Rotation;

	static GAISeq* CreateInstance() { return 0; }
	virtual bool Init(int iMyIndex) = 0;
	virtual bool Frame(int iMyIndex) = 0;
	virtual bool Render() = 0;
	virtual bool Release() = 0;

	//shared_ptr<GCamera > m_pMainCamera;
	//D3DXMATRIX  m_matWorld;
	//GShape*		m_Box1;
	//GShape*		m_Box2;
	//GShape*		m_Box3;
	//----------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
	virtual HRESULT		CreateResource() = 0;
	virtual HRESULT		DeleteResource() = 0;

	virtual int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;

	virtual ~GAISeq();
protected:
	GAISeq();
};

