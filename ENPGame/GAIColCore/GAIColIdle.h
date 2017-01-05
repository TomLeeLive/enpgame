#pragma once

class GAIColIdle : public GAIColSeq
{
public:
	bool Init(GAICol* iMyIndex);
	bool Frame(GAICol* iMyIndex, D3DXMATRIX matHeroWorld,D3DXMATRIX matHeroWorld2, GHero* pHero);
	bool Render();
	bool Release();


	int	WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	float m_SecondPerFrame;


	D3DXVECTOR3 RandomPoint;
	float TimeCount = 0.0f;
	//----------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
public:
	virtual ~GAIColIdle();
	GAIColIdle();
protected:

};


