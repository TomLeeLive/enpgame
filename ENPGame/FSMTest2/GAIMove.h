#pragma once

class GAIMove : public GSeq
{
public:
	static GSeq* CreateInstance() {
		if (pInstance_ == 0) pInstance_ = new GAIMove;
		return pInstance_;
	}
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

	//----------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
	D3DXVECTOR3 RandomPoint;
	D3DXVECTOR3 RandomDestination;
	

	GTimer * TIme;
	float fTime = 15.0f;
	float m_fSecondPerFrmae = 0.0f;
	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return -1; };
public:
	virtual ~GAIMove();
protected:
	GAIMove();
private:
	static GAIMove *pInstance_;
};

