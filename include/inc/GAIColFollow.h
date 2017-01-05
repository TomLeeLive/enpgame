#pragma once
class GAIColFollow : public GAIColSeq
{
public:

	D3DXVECTOR3 m_vBDestLook;
	D3DXVECTOR3 m_vBRight;
	D3DXVECTOR3 m_vBUp;

	bool Init(GAICol* iMyIndex);
	bool Frame(GAICol* iMyIndex, D3DXMATRIX matHeroWorld, D3DXMATRIX matHeroWorld2, GHero* pHero);
	bool Render();
	bool Release();

	int	WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//----------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
public:
	virtual ~GAIColFollow();
	GAIColFollow();
protected:

};


