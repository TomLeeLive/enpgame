#pragma once
class GAIFollow : public GAISeq
{
public:

	D3DXVECTOR3 m_vBDestLook;
	D3DXVECTOR3 m_vBRight;
	D3DXVECTOR3 m_vBUp;

	bool Init(GNewZombie* iMyIndex);
	bool Frame(GNewZombie* iMyIndex, D3DXMATRIX matHeroWorld);
	bool Render();
	bool Release();

	int hp;

	D3DXVECTOR3 B_Look;
	D3DXMATRIX B_Trans;

	int	WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//----------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
public:
	virtual ~GAIFollow();
	GAIFollow();
protected:

};


