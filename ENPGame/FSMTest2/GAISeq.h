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
	float m_fDistance;
	D3DXVECTOR3 m_vRDestLook;
	D3DXVECTOR3 m_vZRight;
	D3DXVECTOR3 m_vZUp;

	bool		m_bDebug;
	bool		m_bTime;
	GCharacter*	 pChar0;


	//static GAISeq* CreateInstance() { return 0; }
	virtual bool Init(int iMyIndex) = 0;
	virtual bool Frame(int iMyIndex) = 0;
	virtual bool Render() = 0;
	virtual bool Release() = 0;
	void		InitGSeq() {
		m_fDistance = 0.0f;
		m_bDebug = false;
		m_bTime = false;
		m_vRDestLook = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		m_vZRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		m_vZUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//D3DXMatrixIdentity(&m_matWorld);
		//D3DXMatrixIdentity(&Trans);
		//D3DXMatrixIdentity(&Rotation);
	};
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
	GAISeq();
protected:

};

