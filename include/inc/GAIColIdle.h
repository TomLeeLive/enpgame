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
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
public:
	virtual ~GAIColIdle();
	GAIColIdle();
protected:

};


