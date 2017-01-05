#pragma once
class GSeqSingle3S : public GSeq
{
public:
	static GSeq* CreateInstance() {
		if (pInstance_ == 0) pInstance_ = new GSeqSingle3S;
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
	virtual ~GSeqSingle3S() {};
protected:
	GSeqSingle3S() { pInstance_ = 0; };
private:
	static GSeqSingle3S *pInstance_;
};
