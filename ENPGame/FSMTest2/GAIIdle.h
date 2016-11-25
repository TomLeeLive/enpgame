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
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
public:
	virtual ~GAIIdle();
protected:
	GAIIdle();
};


