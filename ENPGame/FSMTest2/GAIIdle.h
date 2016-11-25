#pragma once

class GAIIdle : public GAISeq
{
private:
	static GAIIdle *pInstance_;
public:
	static GAISeq* CreateInstance()
	{
		if (pInstance_ == 0) pInstance_ = new GAIIdle;
		return pInstance_;
	}
	shared_ptr<GCamera > m_pMainCamera;
	D3DXMATRIX  m_matWorld;

	bool Init(int iMyIndex);
	bool Frame(int iMyIndex);
	bool Render();
	bool Release();
	int	WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	D3DXVECTOR3 RandomPoint;
	float TimeCount = 0.0f;
	//----------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
public:
	virtual ~GAIIdle();
protected:
	GAIIdle();
};


