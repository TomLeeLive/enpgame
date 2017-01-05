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
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
public:
	virtual ~GAIColFollow();
	GAIColFollow();
protected:

};


