#pragma once
class GSeqSingle2S : public GSeq
{
public:
	static GSeq* CreateInstance() {
		if (pInstance_ == 0) pInstance_ = new GSeqSingle2S;
		return pInstance_;
	}
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

	//----------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//----------------------------------------------------
	HRESULT		CreateResource() { HRESULT hr; return S_OK; };
	HRESULT		DeleteResource() { HRESULT hr; return S_OK; };

	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return -1; };

public:
	virtual ~GSeqSingle2S() {};
protected:
	GSeqSingle2S() { pInstance_ = 0; };
private:
	static GSeqSingle2S *pInstance_;
};
