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
	float m_fRandTime;
	D3DXVECTOR3 m_vRDestLook;
	D3DXVECTOR3 m_vZRight;
	D3DXVECTOR3 m_vZUp;
	D3DXVECTOR3 m_vLook;

	bool		m_bDebug;
	bool		m_bTime;

	bool		m_bRTime;
	bool		m_bRDebug;

	float fTime;
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

	};

	//----------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//----------------------------------------------------
	virtual HRESULT		CreateResource() = 0;
	virtual HRESULT		DeleteResource() = 0;

	virtual int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;

	virtual ~GAISeq();
	GAISeq();
protected:

};

