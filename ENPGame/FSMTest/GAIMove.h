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
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();

	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return -1; };
public:
	virtual ~GAIMove();
protected:
	GAIMove();
private:
	static GAIMove *pInstance_;
};

